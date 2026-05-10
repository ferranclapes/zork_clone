#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
#include "player.h"

using namespace std;

//--------------------------------------
Room::Room(const char* name, const char* description) : Entity(name, description, nullptr) {
	type = ROOM;
}

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

Exit* Room::GetExit(string exit_name) {
	for (Entity* entity : contains) {
		if (entity->GetType() == EXIT) {
			if (Same(entity->GetName(), exit_name)) {
				return (Exit*)entity;
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

Creature* Room::GetCreatureByName(string creature_name) {
	for (Entity* entity : contains) {
		if (entity->GetType() == CREATURE) {
			if (Same(entity->GetName(), creature_name)) {
				return (Creature*)entity;
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

//--------------------------------------
Player* Room::GetPlayer() {
	for (Entity* entity : contains) {
		if (entity->GetType() == PLAYER) {
			return (Player*)entity;
		}
	}
	return nullptr;
}