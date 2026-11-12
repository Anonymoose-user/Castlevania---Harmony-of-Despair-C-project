# Network plugins (online play)

Online play connects through one **network plugin**: a DLL in the game's
`net\` folder. The game ships with `net\gns.dll`, which uses
GameNetworkingSockets (Valve's open-source library).

## For players

- **Pick a plugin** in CVHDEdit with Mods > Network plugins..., or run
  `install_net_plugin.bat`:
  - `install_net_plugin.bat other.dll` (or drag a .dll onto the .bat) installs a plugin and uses it;
  - `install_net_plugin.bat gns` uses an installed one;
  - `install_net_plugin.bat none` turns online play off.
  The choice is the line `netPlugin <name>` in `save\config.txt`. It takes effect
  the next time the game starts.
- **No plugin, or `none`:** the game runs normally, but Online Play cannot connect.
- **GameNetworkingSockets (gns):** direct connections.
  - LAN games show up in the lobby search.
  - Over the internet, the host shares its lobby code (made from its IP address and
    port) or its `ip:port`, and opens that port (UDP) on its router.
  - There is no lobby service.

## For plugin makers

The interface is `include\Port\cvhd_net_plugin.h` in the modding kit. The template
is `examples\net_plugin\net_plugin.cpp`. A plugin exports
`cvhdNetPlugin()`, which returns a table of functions:

- `init`, `shutdown`;
- `host(port, name)`, `join(address, name)`, `leave`;
- `send(slot, data, size, reliable)`, where slot -1 means everyone;
- `poll`, called once a frame on the game's thread.

The plugin reports back through the `CvhdNetHost` the game passes to `init`:

- `receive(fromSlot, data, size)`: hand over every game packet unchanged;
- `peerJoined(slot, name)` and `peerLeft(slot)`;
- `assigned(slot, hostClockMs)`: the client's own slot.

There are up to 6 players, and slot 0 is the host.

A lobby service is optional: `lobbyCreate`, `lobbyUpdate`, `lobbyDestroy` and
`lobbySearch`.
- With these, the game's lobby search lists the plugin's lobbies.
- A typed 10-character code is looked up with `lobbySearch(code)`.
- The host's lobby code is passed to `lobbyCreate`.
- The address each lobby returns is what `join` gets.
