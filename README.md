# ![Void](https://github.com/whimzala/Void/blob/main/Images/void_main.png)
# Void
<table>
<tr>
<td>
What started as a project dedicated to creating an in-game map/radar for Among Us turned into a full menu with way more features than originally planned for..
</td>
</tr>
</table>

### Using Void
To use Void, you will need some type of .dll injector. I will not be linking one, however if you have Cheat Engine that will suffice.

Set up steps:

- Download all the file from [here](https://github.com/whimzala/Void/blob/master/Final)
- Extract to whatever location suits you, I just put it in the main directory of Among Us
- Run Among Us
- Open your .dll injector of choice
- Go back to Among Us
- Inject the .dll once the game starts and in the main menu
- Once injected, press the insert key (some laptops might require you to press fn+insert)

If for some reason the key isn't working you can build the project yourself, and change the keys in [main.cpp](https://github.com/whimzala/Void/blob/master/src/main.cpp) using win32 [Virtual Key Codes ](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)

### Void Features
#### Self
- Change the Kill Timer (setting to 0 will keep it at 0)
- Change Player speed
- Change Report Distance
- Change Emergency meeting amounts
- Set player hat
- Set player pet
- Set player skin
- Set player color
- Noclip
- Danny Phantom (ghost mode)
- Speed multiplier (player speed * this value)
- Light radius
#### Players (other players)
- Display basic information of player
- Goto (teleports you to them)
- Bring (teleports them to you)
- Voided (teleports them to 9999999,9999999)
- Force Meeting
- Kick
#### Map
- Show game map
- Show ghosts on map
- Show vents on map
- Show area names on map
- Change the maps background opacity (alpha)
- Change the maps player icon size
#### Settings
- Log game data (output imposter, deaths, etc) to the log
- Map Debugging (enable debug settings for the map)
- Break Server
```
This will make the server constantly vote until it freezes around the table, essentially.
```

### Radar/Map
Void supports all three maps currently in Among Us, however I have no idea how they will appear on other screens, at which this point unless an issue request is made making me aware of this you will have to use the map debugging settings to find what works for you and build the project yourself.

- Skeld
![Skeld](https://github.com/whimzala/Void/blob/main/Images/void_main.png)
- HQ

- Polus

### Known bugs (bugs with * are priority for future updates)

- Not injecting the .dll on the main screen will cause a crash
- Disabling noclip outside of a game will cause a crash *
- Logged data will not clear causing future logs to not send *
- Players tab will crash due to one of the players being null *

## [License](https://github.com/whimzala/Void/blob/master/LICENSE)

MIT © [Whimzala](https://github.com/whimzala)
