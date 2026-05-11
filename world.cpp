#include <iostream>
#include "world.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"
#include "useful.h"

//--------------------------------------
World::World() {
	InitializeWorld();
}

//--------------------------------------
World::~World() {
	for (Entity* e : entities) {
		delete e;
	}
	entities.clear();
}

//--------------------------------------
void World::InitializeWorld() {
	Room* room1 = new Room("Room 1", "This is a room called Room 1", false);
	Room* room2 = new Room("Room 2", "This is a room called Room 2", true);
	Room* room3 = new Room("Room 3", "This is a room called Room 3", false);
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);


	Exit* exit1 = new Exit("Little Path", EAST, WEST, room1, room2, false, false);
	Exit* exit2 = new Exit("Door", NORTH, SOUTH, room2, room3, false, true);
	entities.push_back(exit1);
	entities.push_back(exit2);


	Item* sword = new Item("Sword", "A shiny silver sword", room1, WEAPON);
	Item* box = new Item("Box", "A cardboard box", room1, CONTAINER);
	Item* letter = new Item("Letter", "Welcome to my clone of Zork! Thanks for playing, I hope you enjoy it :)", box, READABLE);
	Item* key = new Item("Key", "An old and rusty key", room2, MISC);
	Item* flashlight = new Item("Flashlight", "A small flashlight, it can be turned on to illuminate dark places", room1, LIGHT_SOURCE);
	entities.push_back(sword);
	entities.push_back(box);
	entities.push_back(letter);
	entities.push_back(key);
	entities.push_back(flashlight);

	exit2->SetKey(key);


	Creature* troll = new Creature("troll", "A big and nasty troll", room2, false);
	entities.push_back(troll);


	player = new Player("Player", "This is the player", room1);
	entities.push_back(player);

	player->Look();
}

//--------------------------------------
void World::ResetWorld() {
	for (Entity* e : entities) {
		delete e;
	}
	entities.clear();
	InitializeWorld();
}

//--------------------------------------
bool World::Update(vector<string> args) {
	if (!player->IsAlive()) {
		return false;
	}
	CommandReturnValue command_return_value = VALID_COMMAND;
	if (args.size() > 0) {
		 command_return_value = ParseCommand(args);
		if (command_return_value == VALID_COMMAND) {
			for (Entity* e : entities) {
				if (e->GetType() != PLAYER) {
					e->Update();
				}
			}

		}
		else if (command_return_value == INVALID_COMMAND) {
			cout << "\nSorry, I don't understand that command. ";
		}
	}
	if (!player->IsAlive()) {
		return false;
	}
	
	return true;
}

//--------------------------------------
CommandReturnValue World::ParseCommand(vector<string> args) {
	CommandReturnValue valid_command = VALID_COMMAND;
	bool valid_parameters = true;
	if (player->IsResting()) {
		if (Same(args[0], "stop") || Same(args[0], "wake") || Same(args[0], "no") || Same(args[0], "n")) {
			player->StopResting();
		}
		else if (Same(args[0], "yes") || Same(args[0], "continue") || Same(args[0], "rest") || Same(args[0], "y")) {
			valid_parameters = player->Rest();
		}
		else {
			valid_command = INVALID_COMMAND;
		}
	}

	else {
		switch (args.size()) {
		case 1:
			if (Same(args[0], "look")) {
				player->Look();
				break;
			}
			else if (Same(args[0], "east") || Same(args[0], "west") || Same(args[0], "north") || Same(args[0], "south")
				|| Same(args[0], "e") || Same(args[0], "w") || Same(args[0], "n") || Same(args[0], "s")) {
				valid_parameters = player->Go(StringToDirection(args[0]));
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
				valid_parameters = player->Attack(false);
				break;
			}
			else if (Same(args[0], "kill")) {
				valid_parameters = player->Attack(true);
				break;
			}
			else if (Same(args[0], "diagnose")) {
				player->Diagnose();
				break;
			}
			else if (Same(args[0], "rest")) {
				valid_parameters = player->Rest();
				break;
			}
			else {
				valid_command = INVALID_COMMAND;
			}
			break;

		case 2:
			if (Same(args[0], "go")) {
				player->Go(StringToDirection(args[1]));
				break;
			}
			else if (Same(args[0], "look") || Same(args[0], "examine") || Same(args[0], "check")) {
				valid_parameters = player->Examine(args[1]);
				break;
			}
			else if (Same(args[0], "take")) {
				valid_parameters = player->Take(args[1]);
				break;
			}
			else if (Same(args[0], "drop")) {
				valid_parameters = player->Drop(args[1]);
				break;
			}
			else if (Same(args[0], "open")) {
				valid_parameters = player->Open(args[1]);
				break;
			}
			else if (Same(args[0], "close")) {
				valid_parameters = player->Close(args[1]);
				break;
			}
			else if (Same(args[0], "attack")) {
				valid_parameters = player->Attack(args[1], false);
				break;
			}
			else if (Same(args[0], "kill")) {
				valid_parameters = player->Attack(args[1], true);
				break;
			}
			else if (Same(args[0], "equip")) {
				valid_parameters = player->Equip(args[1]);
				break;
			}
			else if (Same(args[0], "unequip")) {
				player->Unequip();
				break;
			}
			else if (Same(args[0], "read")) {
				valid_parameters = player->Read(args[1]);
				break;
			}
			else {
				valid_command = INVALID_COMMAND;
			}
			break;

		case 3:
			if (Same(args[0], "turn") && Same(args[1], "on")) {
				valid_parameters = player->TurnOn(args[2]);
				break;
			}
			else if (Same(args[0], "turn") && Same(args[1], "off")) {
				valid_parameters = player->TurnOff(args[2]);
				break;
			}
			else {
				valid_command = INVALID_COMMAND;
				break;
			}
			break;
		case 4:
			if ((Same(args[0], "unlock") || Same(args[0], "open")) && (Same(args[2], "with") || Same(args[2], "using"))) {
				Directions dir = StringToDirection(args[1]);
				if (dir != ERROR) {
					valid_parameters = player->Unlock(dir, args[3]);
				}
				else {
					valid_parameters = player->Unlock(args[1], args[3]);
				}
				break;
			}
			else if ((Same(args[0], "lock") || Same(args[0], "close")) && (Same(args[2], "with") || Same(args[2], "using"))) {
				Directions dir = StringToDirection(args[1]);
				if (dir != ERROR) {
					valid_parameters = player->Lock(dir, args[3]);
				}
				else {
					valid_parameters = player->Lock(args[1], args[3]);
				}
				break;
			}
			else if (Same(args[0], "put") && Same(args[2], "in")) {
				valid_parameters = player->Put(args[1], args[3]);
				break;
			}
			else if ((Same(args[0], "take") && Same(args[2], "from")) || (Same(args[0], "take") && Same(args[2], "from"))) {
				valid_parameters = player->TakeFrom(args[1], args[3]);
				break;
			}
			else {
				valid_command = INVALID_COMMAND;
			}
			break;

		default:
			valid_command = INVALID_COMMAND;
			break;
		}
	}


	if (!valid_parameters && valid_command == VALID_COMMAND) {
		valid_command = WRONG_PARAMETERS;
	}
	return valid_command;
}

//--------------------------------------
int World::GameOver(vector<string> args) {
	if (args.size() > 0 && (Same(args[0], "y") || Same(args[0], "yes"))) {
		return 1;
	}
	else if (args.size() > 0 && (Same(args[0], "n") || Same(args[0], "no"))) {
		return 2;
	}
	return 0;
}