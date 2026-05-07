#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"

//--------------------------------------
Player::Player(const char* name, const char* description, Room* room) : Creature(name, description, room) {
	type = PLAYER;
}

//--------------------------------------
Player::~Player() {}

//--------------------------------------
void Player::Look() {
	parent->Look();
}

//--------------------------------------
void Player::Go(Directions dir) {

	Room* current_room = GetCurrentRoom();

	Exit* exit = current_room->GetExit(dir);

	if (exit == nullptr) {
		cout << "\nThere is no exit to the " << DirectionToString(dir);
		return;
	}
	
	if (exit->is_locked) {
		cout << "\nThe " << exit->name << " is locked";
		return;
	}

	parent = exit->GetDestinationFrom(current_room);
	cout << "\nYou go to the " << DirectionToString(dir);
	Look();
}

//--------------------------------------
void Player::Take(string item_name) {
	Room* current_room = GetCurrentRoom();
	Item* item = current_room->GetItemByName(item_name);
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return;
	}
	inventory.push_back(item);
	current_room->contains.remove((Entity*)item);
	cout << "\nYou take the " << item_name;
}

//--------------------------------------
void Player::Inventory() {
	if (inventory.empty()) {
		cout << "\nYour inventory is empty.";
		return;
	}
	cout << "\nYou have this items in your inventory:";
	for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
		cout << "\n- " << (*it)->name;
	}
}

//--------------------------------------
void Player::Examine(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = current_room->GetItemByName(item_name);
	
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return;
	}
	
	item->Examine();
}

