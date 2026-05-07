#include <iostream>
#include "creature.h"
#include "room.h"
#include "exit.h"
#include "useful.h"

//--------------------------------------
Creature::Creature(const char* name, const char* description, Room* room) : Entity(name, description, (Entity*) room) {
	type = CREATURE;
	hp = 1;
}

//--------------------------------------
Creature::~Creature() {}

//--------------------------------------
void Creature::Look() {
	cout << "\n" << name;
	if (!IsAlive()) {
		cout << " is dead.";
	}
	cout << "\n" << description;
}

//--------------------------------------
void Creature::Go(Directions dir) {
	if (!IsAlive()) {
		return;
	}

	Room* current_room = GetCurrentRoom();
	Exit* exit = current_room->GetExit(dir);

	if (exit == nullptr) {
		return;
	}

	if (exit->is_locked) {
		return;
	}

	if (current_room->PlayerInRoom()) {
		cout << "\nThe " << name << " goes to the " << DirectionToString(dir);
	}

	parent = exit->GetDestinationFrom(current_room);
}

//--------------------------------------
void Creature::Take(string item_name) {
	if (!IsAlive()) {
		return;
	}
	Room* current_room = GetCurrentRoom();
	Item* item = current_room->GetItemByName(item_name);
	if (item == nullptr) {
		return;
	}
	inventory.push_back(item);
	current_room->contains.remove((Entity*)item);
	cout << "\nThe " << name << " takes the " << item_name;
}

//--------------------------------------
Room* Creature::GetCurrentRoom() {
	return (Room*)parent;
}

//--------------------------------------
bool Creature::IsAlive() {
	return hp > 0;
}
