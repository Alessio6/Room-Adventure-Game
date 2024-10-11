# Room Adventure Game

This is a simple text-based adventure game written in C++. The player navigates through rooms, picking up items such as a sword, shield, map, and potion. Players can move in four directions (North, South, West, East), pick up items, drop items, and view their inventory. The game is designed for a terminal-based interface.

## Features
- Navigate between rooms by typing **north**, **south**, **west**, or **east**.
- Some rooms have limited exits (you cannot always move in every direction).
- Pick up items in rooms by using the **get** command followed by the item’s code.
- Drop items from your inventory using the **drop** command followed by the item’s code.
- Check your current inventory at any time by typing **inventory**.

## Items
- **Sword** (`000`): Can be picked up if found in the same room.
- **Shield** (`001`): Can be picked up if found in the same room.
- **Map** (`002`): Can be picked up if found in the same room.
- **Potion** (`003`): Can be picked up if found in the same room.

## Commands
- **north**, **south**, **west**, **east**: Move to an adjacent room.
- **get [code]**: Pick up an item using its code if it's in the current room.
- **drop [code]**: Drop an item from your inventory using its code.
- **inventory**: Displays a list of items currently in your inventory.

