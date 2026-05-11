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
	Room* room_dungeon_entrance = new Room("Dungeon Entrance", "You are in at the edge of a forest. To the south, there is a tall cliff you can't climb.", false);
	Room* room_forest = new Room("Forest", "You are in a dense forest. Trees are all around you and you can hear some birds chirping. To the north, you see a small wooden hut.", false);
	Room* room_house_entrance = new Room("House Entrance", "You are inside the house. This room is quite small.", false);
	Room* room_messy_room = new Room("Messy Room", "You are in a messy room. Things are scattered everywhere.", false);
	Room* room_house_attic = new Room("House Attic", "You are in the attic of the house. It's very dusty and there are some cobwebs.", true);
	Room* room_dungeon = new Room("Dungeon", "You are in a dark and damp dungeon. The air is thick with the smell of mold.", true);
	Room* room_treasure = new Room("Treasure Room", "You are in a room filled with treasure! There are piles of gold coins, jewels, and other valuable items.", false);
	entities.push_back(room_dungeon_entrance);
	entities.push_back(room_forest);
	entities.push_back(room_house_entrance);
	entities.push_back(room_messy_room);
	entities.push_back(room_house_attic);
	entities.push_back(room_dungeon);
	entities.push_back(room_treasure);


	Item* sword = new Item("Sword", "A shiny silver sword", room_messy_room, WEAPON);
	Item* box = new Item("Box", "A cardboard box", room_messy_room, CONTAINER);
	Item* letter = new Item("Letter", "Welcome to my clone of Zork! Thanks for playing, I hope you enjoy it :)", box, READABLE);
	Item* key = new Item("Key", "An old and rusty key", room_dungeon_entrance, MISC);
	Item* flashlight = new Item("Flashlight", "A small flashlight, it can be turned on to illuminate dark places", room_house_entrance, LIGHT_SOURCE);
	Item* coin = new Item("Coin", "A gold coin, it might be valuable", room_house_attic, MISC);
	entities.push_back(sword);
	entities.push_back(box);
	entities.push_back(letter);
	entities.push_back(key);
	entities.push_back(flashlight);
	entities.push_back(coin);


	Exit* exit_dunent_for = new Exit("Forest Path", "little path through the trees and plants of the forest", EAST, WEST, room_dungeon_entrance, room_forest, false);
	Exit* exit_for_houent = new Exit("Wooden Door", "wooden door", NORTH, SOUTH, room_forest, room_house_entrance, false);
	Exit* exit_houent_mes = new Exit("Rotten Door", "rotten simple door", EAST, WEST, room_house_entrance, room_messy_room, false);
	Exit* exit_houent_att = new Exit("Ladder", "old and creaky ladder", UP, DOWN, room_house_entrance, room_house_attic, false);
	Exit* exit_dunent_dun = new Exit("Stone Stairs", "stone stairs leading down to the dungeon", DOWN, UP, room_dungeon_entrance, room_dungeon, true);
	exit_dunent_dun->SetKey(key);
	Exit* exit_dun_tre = new Exit("Iron Door", "heavy iron door", WEST, EAST, room_dungeon, room_treasure, true);

																					//TODO: Add key for iron door

	entities.push_back(exit_dunent_for);
	entities.push_back(exit_for_houent);
	entities.push_back(exit_houent_mes);
	entities.push_back(exit_houent_att);
	entities.push_back(exit_dunent_dun);
	entities.push_back(exit_dun_tre);
	


	Creature* merchant = new Creature("Merchant", "A moody looking merchant, he seems to be boddered by your presence", room_forest, false);
	key->ChangeParent(merchant);
	Creature* troll = new Creature("Troll", "A big and nasty troll", room_dungeon, true);
	entities.push_back(troll);
	entities.push_back(merchant);

	DialogueLine merchand_line0 = { "Hmm... Another adventurer? Who are you?\nNo, don't answer that, I don't care.\nSame as the others: If you want the key, you will have to pay it.", nullptr, nullptr, 1};
	DialogueLine merchan_line1 = { "What? I already told you. \nNo coin, no key.", coin, nullptr, 2 };
	DialogueLine merchand_line2 = { "Hmm... Yeah, this coin will do.\nHere's the key, now get out of here.", nullptr, key, 3 };
	DialogueLine merchand_line3 = { "I already gave you the key. I don't have anything else.\nAt least not for you. Leave me alone", nullptr, nullptr, 3 };
	merchant->AddDialogueLine(0, merchand_line0);
	merchant->AddDialogueLine(1, merchan_line1);
	merchant->AddDialogueLine(2, merchand_line2);
	merchant->AddDialogueLine(3, merchand_line3);



	player = new Player("Player", "This is the player", room_dungeon_entrance);
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
			if (Same(args[0], "look") || Same(args[0], "l")) {
				player->Look();
				break;
			}
			else if (Same(args[0], "east") || Same(args[0], "west") || Same(args[0], "north") || Same(args[0], "south") || Same(args[0], "up") || Same(args[0], "down")
				|| Same(args[0], "e") || Same(args[0], "w") || Same(args[0], "n") || Same(args[0], "s") || Same(args[0], "u") || Same(args[0], "d")) {
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
			else if (Same(args[0], "talk")) {
				valid_parameters = player->Talk(args[1]);
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
			else if (Same(args[0], "put")) {
				valid_parameters = player->Put(args[1], args[2]);
				break;
			}
			else if (Same(args[0], "take")) {
				valid_parameters = player->TakeFrom(args[1], args[2]);
				break;
			}
			else if (Same("talk", args[0]) && Same("to", args[1])) {
				valid_parameters = player->Talk(args[2]);
				break;
			}
			else if (Same("give", args[0])) {
				valid_parameters = player->Give(args[1], args[2]);
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
			else if (Same("give", args[0]) && Same("to", args[2])) {
				valid_parameters = player->Give(args[1], args[3]);
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