-- example_bat.lua - a Lua enemy. A stage spawns it by the name LUA_example_bat.
-- Phase 1: flies after the nearest player and bites (a short hit box).
-- Phase 2 (below half HP): faster, and fires a shot if SHOT_ID is set.

local SHOT_ID = 0   -- a data/shot/mod_shots.json id from an enabled mod; 0 = no shots

return {
    sprite  = "data/enemy/dll_fcbat/p_fcbat.opd",
    hp      = 120,
    attack  = 15,
    defense = 0,
    boss    = false,
    ground  = false,   -- flies
    contact = true,    -- touching it hurts

    onStart = function(e)
        e.data.phase = 1
        e.state = "chase"
        e:anim(0, true)
    end,

    onTick = function(e, dt)
        local p = e:nearestPlayer()
        local speed = e.data.phase == 1 and 60 or 110

        if e.state == "chase" then
            e:facePlayer()
            local d = math.max(p.dist, 1)
            e:move(p.dx / d * speed, (p.dy - 20) / d * speed)
            if p.dist < 40 then
                e.state = "bite"
            elseif e.data.phase == 2 and SHOT_ID > 0 and e.time > 2 then
                e:shotAt(SHOT_ID, 10, 0, 180)
                e.time = 0
            end
        elseif e.state == "bite" then
            e:move(0, 0)
            if not e.data.bit then
                e:box(0, -16, 32, 32, 0, 0.2)   -- damage 0 = the enemy's attack
                e.data.bit = true
            end
            if e.time > 0.6 then
                e.data.bit = false
                e.state = "chase"
            end
        end
    end,

    onDamage = function(e, amount)
        if e.data.phase == 1 and e.hp < e.maxHp / 2 then
            e.data.phase = 2
            print("example_bat: phase 2")
        end
    end,

    onDeath = function(e)
        print("example_bat: defeated")
    end,
}
