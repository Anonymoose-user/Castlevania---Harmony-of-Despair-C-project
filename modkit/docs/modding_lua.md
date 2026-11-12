# Lua scripting for mods

The game runs Lua 5.4 scripts from mods. There are two kinds:

- **Event scripts** react to things that happen in the game (a stage starts, an
  enemy dies, a player is hit) and can change some of them (the damage taken).
- **Lua enemies** are enemies whose behaviour is a Lua script.

A ready-made example is the `lua_template` mod (`templates/lua` in the modding
kit): turn it on in Manage Mods and read its `README.txt`.

## Where scripts go

| What | File in your mod | Runs |
|---|---|---|
| Event script | `data/scripts/<anything>.lua` | once at the first game frame, again after F5 |
| Lua enemy | `data/enemy/script/<name>.lua` | for each enemy a stage spawns as `LUA_<name>` |

- Event scripts of every enabled mod are loaded, lowest-priority mod first, files
  by name. A higher-priority mod's script loads later, so its listeners run after
  the others' (with the same priority) and can override what they did.
- A Lua enemy file is found through the mod overlay like any game file: the
  highest-priority mod that has `data/enemy/script/<name>.lua` wins.
- Each event script has its own globals; scripts cannot see each other's variables.

## Event scripts

```lua
events.on("enemyKilled", function(ev)
    print(ev:get("name") .. " died")
end)
```

`events.on(name, function(ev) ... end [, priority])` registers a listener. Higher
priority runs first (default 0). Return `true` from the function to stop later
listeners of that event.

The `ev` object (only valid inside the function):

| Method | What |
|---|---|
| `ev:get(field)` | a field: integer, number or string; `nil` if the event has no such field. Handles are integers |
| `ev:set(field, value)` | change an existing field (seen by later listeners only); returns true if done |
| `ev:result()` | the event's result number (e.g. the damage), `nil` if the event has none |
| `ev:setResult(v)` | change the result; the game uses it after all listeners ran |
| `ev:cancel()` | cancel the event (only events marked cancellable); later listeners do not run |
| `ev:name()` | the event's name |

### Events and fields

| Event | Fields | Result / cancel |
|---|---|---|
| `frame` | `dt` (seconds) | - |
| `roomEnter` | `room` (stage id), `index`, `player` (-1) | - |
| `stageStart` | `stage` (id), `index` | - |
| `stageEnd` | `stage`, `result` (-1 quit, -2 all down, -3 aborted, 1 cleared, 2-4 survival) | - |
| `enemySpawn` | `name`, `enemy`, `x`, `y`, `boss` (0/1) | - |
| `enemyKilled` | `name`, `enemy`, `x`, `y`, `killer` (player slot, -1 unknown), `boss` | - |
| `damageCalc` | `enemy`, `name`, `attacker` (slot or -1), `amount`, `power`, `flags` | result = damage to the enemy; cancellable |
| `playerDamaged` | `player` (slot), `handle`, `amount`, `attacker`, `flags`, `direct` | result = damage power (0 or less: no hit); cancellable |
| `itemPicked` | `player`, `handle`, `item` (id), `category` | - |
| `shotSpawn` | `category`, `skill`, `owner`, `player`, `x`, `y`, `level` | cancellable (no shot) |

The details of each event are in `modding_hooks.md`.

### The `game` table

Available to every script (event scripts and enemies):

| Function | Returns |
|---|---|
| `game.log(...)` / `print(...)` | writes a line to `cvhd.log`, prefixed `[lua]` |
| `game.playerCount()` | players in the game |
| `game.player(slot)` | `{x, y, hp, handle}` for slot 0-5, or `nil` |
| `game.shot(id, x, y, speed, angle)` | spawns a mod shot (`data/shot/mod_shots.json` id) at x,y; speed in pixels/s, angle in degrees (0 = right, 90 = down). Returns its handle (0 = failed) |
| `game.sound(name)` | plays a sound effect by name; true if played |
| `game.random(lo, hi)` | a whole number from `lo` up to `hi - 1` |
| `game.stageId()`, `game.stageIndex()`, `game.stageActive()` | the current stage (0 / -1 / false when none) |
| `game.difficulty()` | two values: the level number (0 normal, 1 hard, 2 and up a mod's levels) and its name |

Example: half damage to players.

```lua
events.on("playerDamaged", function(ev)
    ev:setResult(ev:result() / 2)
end)
```

## Lua enemies

The file returns a table:

```lua
return {
    sprite  = "data/enemy/dll_fcbat/p_fcbat.opd",  -- sprite file (animations by number)
    hp = 120, attack = 15, defense = 0,
    boss    = false,
    ground  = false,   -- true: kept on the floor; false: flies
    contact = true,    -- touching its body hurts players
    bgm     = "",      -- optional music (bosses)
    onStart  = function(e) end,          -- when it appears
    onTick   = function(e, dt) end,      -- every frame (dt in seconds)
    onDamage = function(e, amount) end,  -- after it lost HP (and is still alive)
    onDeath  = function(e) end,          -- when it dies
    onDeathTick = function(e, dt) end,   -- every frame after it died, until e:remove()
    deathTime = 1.0,   -- without onDeathTick: seconds the dead enemy stays
}
```

All callbacks are optional. A dead enemy stays on screen for `deathTime` seconds;
with `onDeathTick` it stays until the script calls `e:remove()` (at most 60 s). A
boss counts as beaten (the stage is cleared, boss doors open) when it is removed. Put a stage spawn named `LUA_<name>` in a stage (for
example with CVHDEdit's room editor) to place one.

The `e` object:

| Field / method | What |
|---|---|
| `e.x`, `e.y` | position (can be set) |
| `e.hp`, `e.maxHp` | HP (`hp` can be set, 0 to maxHp) |
| `e.state` | a name you choose (string, starts as `""`). Setting it resets `e.time` |
| `e.time` | seconds since `e.state` was last set (can be set) |
| `e.facing` | -1 left, 1 right |
| `e.boss` | true for a boss |
| `e.attack`, `e.defense` | its attack (contact and `e:box` damage) and defence (can be set) |
| `e.maxHp` | can be set too (HP is cut down to it) |
| `e.invulnerable` | true: hits only knock against it, no damage (can be set) |
| `e.immortal` | true: hits never take it below 1 HP (can be set) |
| `e.contact` | touching its body hurts players (can be set) |
| `e.dying` | true after it died |
| `e.handle` | its handle |
| `e.data` | a table of your own for this enemy (per enemy, starts empty) |
| `e:anim(n [, loop [, restart]])` | play sprite animation `n` (loop defaults to true); the same animation with the same loop flag while it still plays is left running (so calling it every tick is safe), `restart` = true plays it from the start anyway |
| `e:animDone()` | true when a non-looping animation finished |
| `e:move(vx, vy)` | set its speed in pixels/s (kept until changed; `vy` ignored for ground enemies) |
| `e:face(dir)` | face left (-1) or right (1); returns the facing |
| `e:facePlayer()` | face the player it targets |
| `e:shot(id, dx, dy, speed, angle)` | a mod shot from its position + (dx, dy), with dx and angle mirrored by its facing (angle 0 = forward, 90 = down) |
| `e:shotAt(id, dx, dy, speed)` | the same, aimed at the target player |
| `e:box(x, y, w, h, damage, time)` | a hit box (x, y = top-left offset, mirrored by facing) lasting `time` seconds; damage 0 = its attack |
| `e:sound(name)` | a sound effect at its position |
| `e:nearestPlayer()` | `{x, y, dx, dy, dist}` of the player it targets |
| `e:random(lo, hi)` | a whole number from `lo` up to `hi - 1` from the enemy's own random stream |
| `e:kill()` | kills it (runs `onDeath`) |
| `e:remove()` | ends a dead enemy (a boss: beaten); a living one just disappears |
| `e:animSpeed(s)` | animation speed (1 = normal) |
| `e:bossBgm([on])` | starts the stage's boss music (`false`: stops it) |
| `e:spawn(name, x, y [, data])` | spawns the Lua enemy `LUA_<name>` at x, y; its `e.data` starts as the `data` table. Returns its handle (0 = failed). Use it for projectiles that must wait, turn or be breakable |

A two-phase example:

```lua
onTick = function(e, dt)
    local p = e:nearestPlayer()
    e:facePlayer()
    local speed = (e.hp < e.maxHp / 2) and 120 or 60
    e:move(p.dx > 0 and speed or -speed, 0)
    if p.dist < 40 and e.time > 1 then
        e:box(0, -20, 30, 30, 0, 0.2)
        e.state = "bite"   -- resets e.time
    end
end,
```

## Player skills

A player skill is `data/scripts/skill/<name>.lua` in a mod: a new move for a
player (a weapon skill, a special attack, a dash, a transformation). Two things
start one:

- **A weapon.** CVHDEdit > Items > Weapons, the weapon's `script` column
  (saved to `data/item/weapon_tuning.json`). Attacking with that weapon runs
  the skill instead of the normal swing.
- **An input command.** CVHDEdit > Skills & commands, a command's "Lua skill"
  (`data/player/commands.json`, column `script`): the motion runs the skill
  instead of a cast. "Only with weapon" makes it that weapon's own skill.

The file returns a table:

| key | meaning |
|---|---|
| `mp` | MP it costs when a weapon starts it (a command uses its own MP cost) |
| `maxTime` | seconds before it ends on its own (5) |
| `lock` | `true`: the player's own controls are held while it runs (default) |
| `onStart(p)` | when it begins |
| `onTick(p, dt)` | every frame (`dt` = 1/60 s) |
| `onEnd(p)` | when it ends (finished, `maxTime`, or the player knocked down) |

`p` is the player while the skill runs:

| read | |
|---|---|
| `p.x`, `p.y` | position (settable) |
| `p.vx`, `p.vy` | speed; `vx` forward (+ = the way the player faces) |
| `p.time` | seconds since it began |
| `p.facing` | 1 right, -1 left |
| `p.mp`, `p.hp` | MP (settable) and HP |
| `p.character` | character id |
| `p.weapon`, `p.attack` | the weapon item that started it and its attack (0 none) |
| `p.invulnerable` | settable: takes no damage while true |
| `p.lock` | settable: holds the player's controls |
| `p.data` | a table of your own for the whole skill |

| call | |
|---|---|
| `p:anim(n [, loop])` | draw the player with animation `n` of the character's sprite file |
| `p:costume(shot [, anim])` | draw a mod sprite shot's sprite in place of the body |
| `p:move(forward [, down])` | keep moving at this speed (px/s) until `p:stop()` |
| `p:stop()` | stop moving |
| `p:hit(w, h [, damage [, dx, dy [, time]]])` | a box that hurts enemies, `dx` ahead and `dy` up; no `damage` = the weapon's attack; lives `time` s (0.1) |
| `p:shot(id [, dx, dy, vx, vy])` | a projectile from mod_shots.json (`vx` forward) |
| `p:sound(name)` | play a sound effect |
| `p:held(button)` | `"up"`, `"down"`, `"forward"`, `"back"`, `"attack"`, `"jump"`, `"skill"` held this frame |
| `p:random(a, b)` | a whole number from a to b |
| `p:finish()` | end the skill |

Every `p:hit` is its own box: spawn them on a timer (as below), not every
frame, or one swing hits many times.

Example (`mods/lua_template/data/scripts/skill/example_dash.lua`): a dash
forward, invulnerable, hitting with the weapon's attack for 0.3 s.

```lua
return {
    mp = 5, maxTime = 2, lock = true,
    onStart = function(p)
        p.invulnerable = true
        p:move(420, 0)
        p.data.nextHit = 0
    end,
    onTick = function(p, dt)
        if p.time < 0.3 then
            if p.time >= p.data.nextHit then
                p:hit(48, 32, nil, 16, 16)
                p.data.nextHit = p.time + 0.1
            end
        else
            p:stop()
            p:finish()
        end
    end,
    onEnd = function(p) p.invulnerable = false end,
}
```

## Sandbox and limits

- Available: the Lua base functions (without `dofile`, `loadfile`, `load`),
  `string` (without `string.dump`), `table`, `math` (without `math.random` and
  `math.randomseed`: use `game.random` or `e:random`), `utf8`, `coroutine`.
- Not available: `io`, `os`, `package`/`require`, `debug`. Scripts cannot read or
  write files.
- One call from the game into a script may run at most 1,000,000 Lua instructions;
  a longer call is stopped with an error. All scripts together may use up to 64 MB.
- Scripts run on the game's worker threads, one at a time. Keep them quick.
- Do not keep `ev` after the listener returns; copy the values you need.
- Debugging: run the game with `CVHD_LUA_TRACE=1` to log (stderr / the game log,
  `[lua trace]`) each Lua enemy's `e:anim` calls, `e.state` changes, changes of
  `e.data.st`, `e.data.state` and `e.data.clip`, position jumps over 64 px in one
  tick (by `onTick` or by anything else) and ticks with `dt` over 0.1 s; at most
  30 lines a second per enemy.

## Errors

An error writes one line to `cvhd.log`:

```
[lua] my_mod/data/scripts/rules.lua: ...rules.lua:12: attempt to index a nil value (script disabled)
```

and turns that script off (for an enemy file: every enemy of that type stops
acting) until the next F5. The game keeps running.

## F5 (reload)

Pressing F5 in game reloads mod settings. Lua is restarted too: every listener is
removed, the Lua state is thrown away and all scripts load again. Enemies already
on screen keep running with the new file, but their `e.data` starts empty and
`onStart` is not called again.

## Online play

- Lua enemy callbacks only run on the **host** (so `e:spawn` only makes enemies there).
  A guest's copy follows the host's
  position and HP (no `onTick` on the guest; it plays animation 0).
- Use `game.random` / `e:random` for randomness, never your own generators.
- Event scripts run on every machine for the events that happen there. Make sure
  every player has the same mods enabled.
