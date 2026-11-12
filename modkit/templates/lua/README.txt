Lua template mod
================

Shows the two kinds of Lua scripts (full guide: docs/modding_lua.md in the
modding kit).

  data/scripts/example_events.lua      event script: logs enemy kills, prints a
                                       line at stage start, and halves damage to
                                       players when HALF_DAMAGE at its top is true.
  data/enemy/script/example_bat.lua    a Lua enemy (LUA_example_bat): a bat that
                                       chases the nearest player and bites, and
                                       gets faster below half HP.

How to try it
-------------
1. Turn the mod on in Manage Mods (it is off by default).
2. Start any stage. The messages appear in cvhd.log, prefixed [lua].
3. Edit a script and press F5 in game to reload it.

Seeing the enemy
----------------
Enemies only appear where a stage record names them. Open CVHDEdit, pick
this mod, open the room editor for a stage, add an enemy record and type
LUA_example_bat as its name, then save. Start that stage with the mod on.

Copy this folder under a new name to start your own mod.
