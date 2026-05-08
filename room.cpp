#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"

using namespace std;

//--------------------------------------
Room::Room(const char* name, const char* description) : Entity(name, description, NULL) {
	type = ROOM;
}

//--------------------------------------
Room::~Room() {}

//--------------------------------------
void Room::Look() {
	cout << "\n" << name;
	cout << "\n" << description;

	for (Entity* entity : contains) {
		if (entity->GetType() == EXIT) {
			Exit* exit = (Exit*)entity;
			exit->Look(this);

		}
	}

	for (Entity* entity : contains) {
		if (entity->GetType() == ITEM) {
			Item* item = (Item*)entity;
			item->Look();
		}
	}

	for (Entity* entity : contains) {
		if (entity->GetType() == CREATURE) {
			Creature* creature = (Creature*)entity;
			creature->Look();
		}
	}
}

//--------------------------------------
Exit* Room::GetExit(Directions dir) {
	for (Entity* entity : contains) {
		if (entity->GetType() == EXIT) {
			Exit* exit = (Exit*)entity;
			if (exit->GetDirectionFrom(this) == dir) {
				return exit;
			}
		}
	}
	return nullptr;
}

//--------------------------------------
Item* Room::GetItemByName(string item_name) {
	for (Entity* entity : contains) {
		if (entity->GetType() == ITEM) {
			if (Same(entity->GetName(), item_name)) {
				return (Item*)entity;
			}
		}
	}
	return nullptr;
}

//--------------------------------------
bool Room::PlayerInRoom() {
	for (Entity* entity : contains) {
		if (entity->GetType() == PLAYER) {
			return true;
		}
	}
	return false;
}

