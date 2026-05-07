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

	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == EXIT) {
			Exit* exit = (Exit*)*it;
			exit->Look(this);

		}
	}

	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == ITEM) {
			Item* item = (Item*)*it;
			item->Look();
		}
	}

	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == CREATURE) {
			Creature* creature = (Creature*)*it;
			creature->Look();
		}
	}
}

//--------------------------------------
Exit* Room::GetExit(Directions dir) {
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == EXIT) {
			Exit* exit = (Exit*)*it;
			if (exit->GetDirectionFrom(this) == dir) {
				return exit;
			}
		}
	}
	return nullptr;
}

//--------------------------------------
Item* Room::GetItemByName(string item_name) {
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == ITEM) {
			if (Same((*it)->GetName(), item_name)) {
				return (Item*)*it;
			}
		}
	}
	return nullptr;
}

//--------------------------------------
bool Room::PlayerInRoom() {
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == PLAYER) {
			return true;
		}
	}
	return false;
}

