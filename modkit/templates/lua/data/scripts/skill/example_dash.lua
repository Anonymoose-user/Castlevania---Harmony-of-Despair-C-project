-- A Lua player skill (docs/modding_lua.md, "Player skills").
-- Give it to a weapon: CVHDEdit > Items > Weapons, column "script" = example_dash
--   (attacking with that weapon runs it instead of the swing).
-- Or to an input command: CVHDEdit > Skills & commands, "Lua skill" = example_dash.
return {
    mp = 5,          -- MP when a weapon starts it (a command uses its own MP cost)
    maxTime = 2,     -- seconds before it ends on its own
    lock = true,     -- the player's own controls are held while it runs

    onStart = function(p)
        p.invulnerable = true
        p:move(420, 0)               -- 420 px/s forward, 0 down
        p.data.nextHit = 0
    end,

    onTick = function(p, dt)
        if p.time < 0.3 then
            if p.time >= p.data.nextHit then   -- a new hit box 10 times a second
                p:hit(48, 32, nil, 16, 16)       -- the weapon's attack, 16 px ahead, 16 px up
                p.data.nextHit = p.time + 0.1
            end
        else
            p:stop()
            p:finish()
        end
    end,

    onEnd = function(p)
        p.invulnerable = false
    end,
}
