-- example_events.lua - an event script (docs/modding_lua.md).
-- Every .lua file in a mod's data/scripts folder runs once when the game
-- starts (and again after F5). Use events.on to react to game events.

-- Set to true to make players take half damage.
local HALF_DAMAGE = false

events.on("stageStart", function(ev)
    print("stage " .. ev:get("stage") .. " started, players: " .. game.playerCount())
end)

events.on("enemyKilled", function(ev)
    local who = ev:get("killer")
    game.log(string.format("%s killed at (%.0f, %.0f) by player %d",
        ev:get("name"), ev:get("x"), ev:get("y"), who))
end)

if HALF_DAMAGE then
    events.on("playerDamaged", function(ev)
        ev:setResult(ev:result() / 2)
    end)
end
