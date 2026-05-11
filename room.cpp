#include <iostream>
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
#include "player.h"

using namespace std;

//--------------------------------------
Room::Room(const char* name, const char* description, bool is_dark) : Entity(name, description, nullptr) {
	type = ROOM;
	this->is_dark = is_dark;
}

//--------------------------------------
void Room::Look() {
	if (is_dark && !IsThereLightSource()) {
		cout << "\nIt's too dark to see anything.";
		return;
	}

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

Item* Room::GetItemFromContainers(string item_name) {
	for (Item* container : GetItemsByType(CONTAINER)) {
		if (container->IsOpen()) {
			Item* item_in_container = nullptr;
			for (Entity* entity : container->GetContains()) {
				if (Same(entity->GetName(), item_name)) {
					item_in_container = (Item*)entity;
					return item_in_container;
				}
			}
		}
	}
	return nullptr;
}

list<Item*> Room::GetItemsByType(ItemType item_type) {
	list<Item*> items_of_type;
	for (Entity* entity : contains) {
		if (entity->GetType() == ITEM) {
			Item* item = (Item*)entity;
			if (item->GetItemType() == item_type) {
				items_of_type.push_back(item);
			}
		}
	}
	return items_of_type;
}

//--------------------------------------
Creature* Room::GetCreatureByName(string creature_name) {
	for (Entity* entity : contains) {
		if (entity->GetType() == CREATURE || entity->GetType() == PLAYER) {
			if (Same(entity->GetName(), creature_name)) {
				return (Creature*)entity;
			}
		}
	}
	return nullptr;
}

//--------------------------------------
list<Creature*> Room::GetHostileCreatures(Creature* hostile_towards_this) {
	list<Creature*> hostile_creatures;
	for (Entity* entity : contains) {
		if (entity->GetType() == CREATURE) {
			Creature* creature = (Creature*)entity;
			if (creature->IsHostile() && creature->GetCombatTarget() == hostile_towards_this && !creature->IsUnconscious()) {
				hostile_creatures.push_back(creature);
			}
		}
	}
	return hostile_creatures;
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

//--------------------------------------
bool Room::IsThereLightSource() {
	for (Entity* entity : contains) {
		if (entity->GetType() == ITEM) {
			Item* item = (Item*)entity;
			if (item->GetItemType() == LIGHT_SOURCE && item->IsTurnedOn()) {
				return true;
			}
		}
		else if (entity->GetType() == CREATURE || entity->GetType() == PLAYER) {
			Creature* creature = (Creature*)entity;
			for (Item* item : creature->GetFromInventory(LIGHT_SOURCE)) {
				if (item->IsTurnedOn()) {
					return true;
				}
			}
		}
	}
	return false;
}