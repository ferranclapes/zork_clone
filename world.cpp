#include "world.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"
#include "useful.h"

//--------------------------------------
World::World() {

	Room* room1 = new Room("Room 1", "This is a room called Room 1");
	Room* room2 = new Room("Room 2", "This is a room called Room 2");
	Room* room3 = new Room("Room 3", "This is a room called Room 3");
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);


	Exit* exit1 = new Exit("Little Path", EAST, WEST, room1, room2, false, false);
	Exit* exit2 = new Exit("Another Path", NORTH, SOUTH, room2, room3, false, true);
	entities.push_back(exit1);
	entities.push_back(exit2);


	Item* item1 = new Item("Item1", "This is an weapon item called Item 1", room1, WEAPON);
	Item* itemContainer = new Item("box", "A carboard box", room1, CONTAINER);
	Item* key = new Item("Key", "An old and rusty key", room2, MISC);
	entities.push_back(item1);
	entities.push_back(itemContainer);
	entities.push_back(key);
	
	exit2->AddKey(key);


	Creature* creature1 = new Creature("Creature1", "This is a creature called Creature 1", room2);
	entities.push_back(creature1);


	player = new Player("Player", "This is the player", room1);
	entities.push_back(player);

	player->Look();
}

//--------------------------------------
World::~World() {
	for (Entity* entity : entities) {
		delete entity;
	}
}

//--------------------------------------
bool World::ParseCommand(vector<string> args) {
	bool valid_command = true;
	switch (args.size()) {
	case 1:
		if (Same(args[0], "look")) {
			player->Look();
			break;
		}
		else if (Same(args[0], "east") || Same(args[0], "west") || Same(args[0], "north") || Same(args[0], "south")
			|| Same(args[0], "e") || Same(args[0], "w") || Same(args[0], "n") || Same(args[0], "s")) {
			player->Go(StringToDirection(args[0]));
			break;
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i")) {
			player->Inventory();
			break;
		}
		else {
			valid_command = false;
		}
		break;

	case 2:
		if (Same(args[0], "go")) {
			player->Go(StringToDirection(args[1]));
			break;
		}
		else if (Same(args[0], "look") || Same(args[0], "examine")) {
			player->Examine(args[1]);
			break;
		}
		else if (Same(args[0], "take")) {
			player->Take(args[1]);
			break;
		}
		else if (Same(args[0], "drop")) {
			player->Drop(args[1]);
			break;
		}
		else if (Same(args[0], "open")) {
			player->Open(args[1]);
			break;
		}
		else if (Same(args[0], "close")) {
			player->Close(args[1]);
			break;
		}
		else {
			valid_command = false;
		}
		break;

	case 3:
		break;
	case 4:
		if (Same(args[0], "unlock") && (Same(args[2], "with") || Same(args[2], "using"))) {
			player->Unlock(StringToDirection(args[1]), args[3]);
		}
		else if (Same(args[0], "put") && Same(args[2], "in")) {
			player->Put(args[1], args[3]);
		}
		else if ((Same(args[0], "take") && Same(args[2], "from")) || (Same(args[0], "take") && Same(args[2], "from"))) {
			player->TakeFrom(args[1], args[3]);
		}
		else {
			valid_command = false;
		}
		break;

	default:
		valid_command = false;
		break;
	}
	return valid_command;
}