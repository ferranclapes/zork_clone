#include "world.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"
#include "useful.h"

//--------------------------------------
World::World() {

	start_time = chrono::steady_clock::now();

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


	Item* item1 = new Item("Sword", "A shiny silver sword", room1, WEAPON);
	Item* itemContainer = new Item("box", "A cardboard box", room1, CONTAINER);
	Item* key = new Item("Key", "An old and rusty key", room2, MISC);
	entities.push_back(item1);
	entities.push_back(itemContainer);
	entities.push_back(key);
	
	exit2->AddKey(key);


	Creature* creature1 = new Creature("Creature1", "This is a creature called Creature 1", room2, true);
	entities.push_back(creature1);


	player = new Player("Player", "This is the player", room1);
	entities.push_back(player);

	player->Look();
}

//--------------------------------------
World::~World() {
	for (Entity* e : entities) {
		delete e;
	}
	entities.clear();
}


//--------------------------------------
bool World::Update(vector<string> args) {
	bool return_value = true;

	if (args.size() > 0) {
		return_value = ParseCommand(args);
		if (return_value) {
			for (Entity* e : entities) {
				e->Update();
			}

		}
	}
	return return_value;
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
			valid_command = player->Go(StringToDirection(args[0]));
			break;
		}
		else if (Same(args[0], "inventory") || Same(args[0], "i")) {
			player->Inventory();
			break;
		}
		else if (Same(args[0], "unequip")) {
			player->Unequip();
			break;
		}
		else if (Same(args[0], "attack")) {
			valid_command = player->Attack(false);
			break;
		}
		else if (Same(args[0], "kill")) {
			valid_command = player->Attack(true);
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
			valid_command = player->Examine(args[1]);
			break;
		}
		else if (Same(args[0], "take")) {
			valid_command = player->Take(args[1]);
			break;
		}
		else if (Same(args[0], "drop")) {
			valid_command = player->Drop(args[1]);
			break;
		}
		else if (Same(args[0], "open")) {
			valid_command = player->Open(args[1]);
			break;
		}
		else if (Same(args[0], "close")) {
			valid_command = player->Close(args[1]);
			break;
		}
		else if (Same(args[0], "attack")) {
			valid_command = player->Attack(args[1], false);
			break;
		}
		else if (Same(args[0], "kill")) {
			valid_command = player->Attack(args[1], true);
			break;
		}
		else if (Same(args[0], "equip")) {
			valid_command = player->Equip(args[1]);
			break;
		}
		else if (Same(args[0], "unequip")) {
			player->Unequip();
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
			valid_command = player->Unlock(StringToDirection(args[1]), args[3]);
		}
		else if (Same(args[0], "put") && Same(args[2], "in")) {
			valid_command = player->Put(args[1], args[3]);
		}
		else if ((Same(args[0], "take") && Same(args[2], "from")) || (Same(args[0], "take") && Same(args[2], "from"))) {
			valid_command = player->TakeFrom(args[1], args[3]);
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