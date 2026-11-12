Castlevania: Harmony of Despair - PC port
=========================================

This folder has the game program, its tools and mods, but NOT the game's data:
This program uses the PS3 version of the game as its basis.
You must provide your own legitimate game files to play.
Required files include the base game and all DLC content

1. Run CVHDDataBuilder.exe. Point it at your copy of the game 
(the folder with USRDIR) and build. 
It writes data.zip next to cvhd.exe.

2. Run cvhd.exe.

Online play: through the network plugin in net\ (gns.dll, GameNetworkingSockets:
LAN search, or share your lobby code / ip:port and open that UDP port).
Another plugin: install_net_plugin.bat other.dll (or CVHDEdit, Mods > Network
plugins...). install_net_plugin.bat none turns online play off.
Modularity allows you to swap out the online solution for one of your preference

Modding: CVHDEdit.exe (the editor), MODDING.md and modkit/ (the C++ / Lua
modding kit). Mods go in mods/; their order is mods/load_order.txt.
