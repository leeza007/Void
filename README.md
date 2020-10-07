# ![Phantom](https://github.com/whimzala/Phantom/blob/master/Images/landing.png)
# Phantom
<table>
<tr>
<td>
Phantom gains access to Noitas lua engine allowing the user free range to do as they please with their scripts/mods and gives the ability to call restricted functions whenever needed.
</td>
</tr>
</table>

### Using Phantom
To use phantom, you will need some type of .dll injector. I will not be linking one, however if you have Cheat Engine that will suffice.

Set up steps:

- Download all the files from [here](https://github.com/whimzala/Phantom/blob/master/CurrentBuild)
- Extract the phantom folder to noitas main directory. 
Example:`C:\Program Files (x86)\Steam\steamapps\common\Noita`
- Run Noita
- Open your .dll injector of choice
- Go back to Noita and start a game (can be new or continued)
- Inject the .dll once the game starts (injecting the .dll on the menu screen has a very high potential to cause issues, more info below)
- Once injected, press the insert key (some laptops might require you to press fn+insert)

If for some reason the key isn't working you can build the project yourself, and change the keys in [dUpdate.cpp](https://github.com/whimzala/Phantom/blob/master/src/dll/dUpdate.cpp) using win32 [Virtual Key Codes ](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)

### Using Phantoms custom functions
Phantom comes with a small set of custom functions, with plans on expanding these in the future.

Functions:

- console(text)
```lua
console("boo!"); -- basic console output, text colored orange
```
- success(text)
```lua
success("boo!"); -- basic console output, text colored green
```
- execute(script)
```lua
execute("GamePrint('boo!');"); -- think of it as loadstring() except errors run through the console naturally.
```
- printstate()
```lua
printstate(); -- will return the current lua states address
```

### Phantoms lua access
Phantom enables a plethora of functions that are restricted by Noita by default, which include:

- The entirety of Noitas restricted mod functions, small example:
```lua
-- this can be called whenever instead of only at mod initilization.
-- test.lua contains GamePrintImportant("Boo!","Got yaaah!");
ModLuaFileAppend("data/scripts/items/spell_refresh.lua", "phantom/test.lua"); -- whenever a spell refreshes is picked up it will now print Boo! Got yaaah!
```
- The entirety of Lua's file I/O functions, small example:
```lua
file = io.open("test.lua", "w"); -- open the file in write mode, will create it if not already there
file:write("boo!"); -- write some text to it
file:close(); -- close the file
```
- The entirety of Lua's os functions, small example:
```lua
os.execute("cmd.exe"); -- would be like doing system("cmd.exe") in C, opens command prompt
os.execute("echo boo!"); -- echo to the command prompt
```
- The entirety of Lua's debug functions, small example:
```lua
localPlayer = EntityGetWithTag("player_unit")[1]; -- get the localplayer
setfenv(1,{_G = _G}); -- set the environment using _G from the old
_G.print(_G.localPlayer) -- print localPlayer
```
- The entirety of Lua's ffi functions, small example:
```lua
-- for the most part this is just running C from lua
ffi.cdef[[
typedef const char* boo;
const char* scaredYa(boo text);
]]
```
- The entirety of Lua's bitop functions, small example:
```lua
function printHex(d)
  print("0x"..bit.tohex(d));
end;
```

### Console commands (as of 2.5.0)

### Known bugs (bugs with * are priority)

- Injecting the .dll on the main menu screen will cause the file and phantom functions to fail registering.
- Injecting the .dll on the main menu screen will sometimes make the lua_state unobtainable from the hook and halt the console.
- Sometimes when injecting prebuilt scripts it will say it loaded successfully, however you will need to press the button again for it to actually load successfully.
- Using the functions below will crash the game, working to find a fix asap. *
```lua
BiomeMapLoad_KeepPlayer();
BiomeMapLoad();
```

## [License](https://github.com/whimzala/Phantom/blob/master/LICENSE)

MIT © [Whimzala](https://github.com/whimzala)
