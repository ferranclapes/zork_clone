#include <iostream>
#include "creature.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "useful.h"

//--------------------------------------
Creature::Creature(const char* name, const char* description, Room* room, bool is_hostile) : Entity(name, description, (Entity*) room) {
	type = CREATURE;
	this->is_hostile = is_hostile;
}

//--------------------------------------
void Creature::Update() {
	if (!IsAlive()) {
		return;
	}

	if (is_hostile) {
		if (combat_target == nullptr) {
			combat_target = (Creature*)GetCurrentRoom()->GetPlayer();	// Returns nullptr if the player isn't in the room
		}
		if (combat_target != nullptr) {
			Attack();
			if (!combat_target->IsAlive()) {
				combat_target = nullptr;
			}
		}
	}
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
bool Creature::Go(Directions dir) {
	if (!IsAlive()) {
		return false;
	}

	Room* current_room = GetCurrentRoom();
	Exit* exit = current_room->GetExit(dir);

	if (exit == nullptr) {
		return false;
	}

	if (exit->IsLocked()) {
		return false;
	}

	if (current_room->PlayerInRoom()) {
		cout << "\nThe " << name << " goes to the " << DirectionToString(dir);
	}

	ChangeParent(exit->GetDestinationFrom(current_room));
	return true;
}

//--------------------------------------
bool Creature::Take(string item_name) {
	if (!IsAlive()) {
		return false;
	}
	Room* current_room = GetCurrentRoom();
	Item* item = current_room->GetItemByName(item_name);
	if (item == nullptr) {
		return false;
	}
	inventory.push_back(item);
	contains.push_back(item);
	current_room->RemoveContainedEntity(item);
	cout << "\nThe " << name << " takes the " << item_name;
	return true;
}

//--------------------------------------
bool Creature::Unlock(Directions dir, string key_name) {
	if (!IsAlive()) {
		return false;
	}
	Room* current_room = GetCurrentRoom();
	Exit* exit = current_room->GetExit(dir);
	if (exit == nullptr) {
		return false;
	}
	if (!exit->IsLocked()) {
		return false;
	}
	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (item->GetName() == key_name) {
			exit->Unlock();
			if (current_room->PlayerInRoom()) {
				cout << "\nThe " << name << " unlocks the " << exit->GetName() << " to the " << DirectionToString(dir);
			}
			return true;
		}
	}
	return false;
}

//--------------------------------------
Item* Creature::GetFromInventory(string item_name) {
	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (Same(item->GetName(), item_name)) {
			return item;
		}
	}
	return nullptr;
}

//--------------------------------------
bool Creature::Equip(string item_name) {
	if (!IsAlive()) {
		return false;
	}

	bool player_in_room = GetCurrentRoom()->PlayerInRoom();

	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (Same(item->GetName(), item_name)) {
			if (item->GetItemType() == WEAPON) {
				equipped_weapon = item;
				if (player_in_room) {
					cout << "\nThe " << name << " equips the " << item_name;
				}
				return true;
			}
			else {
				if (player_in_room) {
					cout << "\nThe " << item_name << " can't be equipped.";
				}
				return false;
			}
		}
	}
	return false;
}

void Creature::Unequip() {
	if (!IsAlive()) {
		return;
	}
	if (equipped_weapon != nullptr) {
		bool player_in_room = GetCurrentRoom()->PlayerInRoom();
		if (player_in_room) {
			cout << "\nThe " << name << " unequips the " << equipped_weapon->GetName();
		}
		equipped_weapon = nullptr;
	}
}

//--------------------------------------
Room* Creature::GetCurrentRoom() {
	return (Room*) GetParent();
}
//--------------------------------------
bool Creature::IsAlive() {
	return health_status != DEAD;
}

//--------------------------------------
void Creature::Attack() {
	if (combat_target == nullptr) {
		return;
	}
	bool player_in_room = GetCurrentRoom()->PlayerInRoom();

	string target_name = combat_target->GetName();
	if (Same(target_name, "Player")) {
		target_name = "you";
	}
	else {
		target_name = "the " + target_name;
	}

	if (combat_target->GetHealthStatus() == UNCONSCIOUS) {
		combat_target->TakeDamage(FATAL_DAMAGE, true);
		return;
	}

	if (equipped_weapon != nullptr) {
		DamageLevel damage = static_cast<DamageLevel>(rand() % 5);
		if (damage == NO_DAMAGE) {
			if (player_in_room) {
				cout << "\nThe " << name << " attacks " << target_name << " with the " << equipped_weapon->GetName() << " but misses.";
			}
			return;
		}
		if (player_in_room) {
			cout << "\nThe " << name << " hits " << target_name << " with the " << equipped_weapon->GetName();
		}
		combat_target->TakeDamage(damage, true);
	}
	else {
		DamageLevel damage = static_cast<DamageLevel>(rand() % 2);
		if (damage == NO_DAMAGE) {
			if (player_in_room) {
				cout << "\nThe " << name << " attacks " << target_name << " but misses.";
			}
			return;
		}
		if (player_in_room) {
			cout << "\nThe " << name << " hits " << target_name << " without any weapon.";
		}
		combat_target->TakeDamage(damage, true);
	}
}

//--------------------------------------
void Creature::TakeDamage(DamageLevel damage, bool fatal_intent) {
	int new_health_status = static_cast<int>(health_status) + static_cast<int>(damage);
	if (new_health_status > DEAD) {
		new_health_status = DEAD;
	}

	health_status = static_cast<HealthStatus>(new_health_status);

	if (health_status >= UNCONSCIOUS && !fatal_intent) {
		health_status = UNCONSCIOUS;
		cout << "\nThe " << name << " has been knocked unconscious.";
	}
	else if (health_status == UNCONSCIOUS && fatal_intent) {
		health_status = DEAD;
	}
	if (health_status >= DEAD) {
		health_status = DEAD;
		cout << "\nThe " << name << " has died.";
	}
}