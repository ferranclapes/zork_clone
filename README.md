# Another Zork Clone

## Authors
* **Ferran Clapés i Costa**

## About the Game
A C++ text-adventure inspired by the classic Zork. This project focuses on object-oriented design and custom command parsing.

## How to Play
1. Download the zip from the [Releases](https://github.com/ferranclapes/zork_clone/releases) section.
2. Extract and run `zork_clone.exe`.
3. Type commands like `go north`, `take sword`, or `inventory` (see `list of commands` below). 

## How to Win (Walkthrough)
1. Go East to the Forest.
2. Talk to the merchant, he will ask for money in exchange for a key
3. Go North inside the hut.
4. Take the flashlight
5. Go East to the Messy Room
6. Take the Sword and equip it. (You can also open the box and read the letter, but it isn't necessary)
7. Go West back to the House Entrance and Go Up to the House Attic.
8. Turn on the flashlight.
9. Take the coin.
10. Go Down and South back to the Forest.
11. Give the coin to the merchant and talk to him. He will give you a key.
12. Go West to the Dungeon Entrance and use the key to open the Down direction (Stairs)
13. Fight the Troll untill he falls uncountious or dies.
14. Go West to the Treasure Room

## License
This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the LICENSE file for details.

## Repository Link
https://github.com/ferranclapes/zork_clone

## List of Commands
-q / quit: Quit the game
- go `direction` / `direction`: Moves in that direction
- look / l: Descrives the room you are in, with the exits, objects, and creatures you can see.
- inventory, i: Lists your inventory.
- attack `creature name`: attacks the creature without fatal intent. You won't kill it, just leave them unconscious.
- kill `creature name`: attacks the creature with fatal intent. You may kill it.
- attack / kill: Attacks the last creature attacked.
- diagnose: Hints at your health status.
- rest: Start resting to regain health.
- look `item name`, examine `item name`, check `item_name`: describes the item.
- take `item name`: Takes the item.
- drop `item name`: Drops the item.
- open `item name`: Open items like boxes.
- close `item name`: Close items like boxes.
- equip `weapon name`: Equips a weapon to use it.
- unequip: Unequips the current weapon.
- read `item name`: Read the item if possible.
- talk `creature name` / talk to `creature name`: Talk to the creature.
- turn on `item name`: Turns on a light source.
- turn off `item name`: Turns off a light source.
- put `item name` in `container name` / put `item name` `container name`: Puts the item inside another item (container) like a box.
- take `item name` from `container name` / take `item name` `container name`: Takes the item from inside another item (container) like a box.
- give `item name` to `creature name` / give `item name` `creature name`: Gives the item to the creature.
- unlock `direction`/`exit name` with/using `item name`: Unlocks the exit in that direction or with that name using the item.
- lock `direction`/`exit name` with/using `item name`: Locks the exit in that direction or with that name using the item.
While resting:
- stop / wake / no / n: Wake up and stop resting.
- continue / rest / yes / y: Continue resting one more turn.
When it's game over:
- yes / y: Try again.
- no / n: Quit the game
