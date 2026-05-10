#include <iostream>
#include "creature.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "useful.h"

//--------------------------------------
Creature::Creature(const char* name, const char* description, Room* room) : Entity(name, description, (Entity*) room) {
	type = CREATURE;
	hp = 1;
}


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

	if (exit->IsLocked()) {
		return;
	}

	if (current_room->PlayerInRoom()) {
		cout << "\nThe " << name << " goes to the " << DirectionToString(dir);
	}

	ChangeParent(exit->GetDestinationFrom(current_room));
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
	current_room->RemoveContainedEntity(item);
	cout << "\nThe " << name << " takes the " << item_name;
}

//--------------------------------------
void Creature::Unlock(Directions dir, string key_name) {
	if (!IsAlive()) {
		return;
	}
	Room* current_room = GetCurrentRoom();
	Exit* exit = current_room->GetExit(dir);
	if (exit == nullptr) {
		return;
	}
	if (!exit->IsLocked()) {
		return;
	}
	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (item->GetName() == key_name) {
			exit->Unlock();
			if (current_room->PlayerInRoom()) {
				cout << "\nThe " << name << " unlocks the " << exit->GetName() << " to the " << DirectionToString(dir);
			}
			return;
		}
	}
}

//--------------------------------------
Room* Creature::GetCurrentRoom() {
	return (Room*) GetParent();
}

//--------------------------------------
bool Creature::IsAlive() {
	return hp > 0;
}
