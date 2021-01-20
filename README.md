# Godotcord - GDNative
A Godot module to integrate the Discord GameSDK into the engine

> This integration is not official and is not supported by the Discord GameSDK Developers.

> Not every functionality of this module has been thoroughly tested. I advise against using it in production.

Godotcord currently compiles for Windows, Linux and Mac.

# Setup

- Clone the godotcord repository recursively
  
The following steps can all be done by running setup.bat (Windows) or setup.sh (Linux/Mac) in the godotcord directory.<br>
If you want to do the setup on your own, here are the steps:
- [Download version 2.5.6 of the Discord Game SDK](https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip)
- Unzip the file
- Copy the files in the cpp into a folder called 'discord-files' in the godotcord directory
- Rename the x86 dlls to discord_game_sdk.32.dll and discord_game_sdk.32.dll.lib
- Copy the all dll's and libs into a folder called libpath in the godotcord directory
- Create a folder called `bin`
  
The next step is to compile godotcord.
First create a custom api.json using your godot executable.
For this execute `GODOT_EXECUTABLE --gdnative-generate-json-api api.json` in a shell/cmd.
Copy the generated api.json into `/path/to/godotcord/godot-cpp`.
Next execute `scons platform=<platform> generate_bindings=yes -j16` in `/path/to/godotcord/godot-cpp`.

You can now build godotcord using `scons platform=<platform>` in `/path/to/godotcord`.

In order to use the GDNative lib you have to copy the resulting shared library in `/path/to/godotcord/bin`  to `/path/to/project/bin`.
Next copy the .gdns and .gdnlib files to `/path/to/project`.

The final step is to copy the following libraries into `/path/to/godotcord/bin`:
- On Windows: Copy the .dll files
- On Linux: Copy the .so file
- On Mac: Copy the .dylib file and rename it to discord_game_sdk.dylib
These files should be in `/path/to/godot/modules/godotcord/libpath` if setup correctly.

You can now use godotcord as GDNative module.

# Documentation

The documentation can be found in the [wiki](https://github.com/Drachenfrucht1/godotcord/wiki)

# License
MIT License<br>
The Discord GameSDK is licensed under the [Discord Developer Terms of Service](https://discord.com/developers/docs/legal)
