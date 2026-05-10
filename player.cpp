#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"

//--------------------------------------
Player::Player(const char* name, const char* description, Room* room) : Creature(name, description, room, false) {
	type = PLAYER;
}


//--------------------------------------
void Player::Look() {
	GetCurrentRoom()->Look();
}

//--------------------------------------
bool Player::Go(Directions dir) {

	if (dir == ERROR){
		cout << "\nThat's not a valid direction.";
		return false;
	}

	Room* current_room = GetCurrentRoom();

	Exit* exit = current_room->GetExit(dir);

	if (exit == nullptr) {
		cout << "\nThere is no exit to the " << DirectionToString(dir);
		return false;
	}
		
	if (exit->IsLocked()) {
		cout << "\nThe " << exit->GetName() << " is locked";
		return false;
	}

	ChangeParent(exit->GetDestinationFrom(current_room));
	cout << "\nYou go to the " << DirectionToString(dir);
	Look();
	return true;
}

//--------------------------------------
bool Player::Take(string item_name) {
	Room* current_room = GetCurrentRoom();
	Item* item = current_room->GetItemByName(item_name);
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return false;
	}
	item->ChangeParent(this);
	cout << "\nYou take the " << item_name;
	return true;
}

//--------------------------------------
bool Player::Drop(string item_name) {
	Item* item_to_drop = nullptr;
	item_to_drop = GetFromInventory(item_name);

	if (item_to_drop == nullptr) {
		cout << "\nYou don't have a " << item_name << ".";
		return false;
	}
	else {
		item_to_drop->ChangeParent(GetCurrentRoom());
		cout << "\nYou drop the " << item_name;
		return true;
	}
}

//--------------------------------------

bool Player::Unlock(Directions dir, string key_name) {
	Exit* exit = GetCurrentRoom()->GetExit(dir);
	if (exit == nullptr) {
		cout << "\nThere is no exit to the " << DirectionToString(dir);
		return false;
	}
	return Unlock(exit, key_name);
}

bool Player::Unlock(string exit_name, string key_name) {
	Exit* exit = GetCurrentRoom()->GetExit(exit_name);
	if (exit == nullptr) {
		cout << "\nThere is no exit named " << exit_name;
		return false;
	}
	return Unlock(exit, key_name);
}

bool Player::Unlock(Exit* exit, string key_name) {
	if (!exit->IsLocked()) {
		cout << "\nThe " << exit->GetName() << " is not locked.";
		return false;
	}
	Item* key = GetFromInventory(key_name);
	if (key == nullptr) {
		cout << "\nYou don't have a " << key_name << ".";
		return false;
	}
	else {
		bool unlocked = exit->Unlock(key);
		if (unlocked) {
			cout << "\nYou unlock the " << exit->GetName() << " with the " << key_name;
		}
		else {
			cout << "\nThe " << key_name << " doesn't fit the " << exit->GetName();
		}
		return unlocked;
	}
}

//--------------------------------------
bool Player::Lock(Directions dir, string key_name) {
	Exit* exit = GetCurrentRoom()->GetExit(dir);
	if (exit == nullptr) {
		cout << "\nThere is no exit to the " << DirectionToString(dir);
		return false;
	}
	return Lock(exit, key_name);
}

bool Player::Lock(string exit_name, string key_name) {
	Exit* exit = GetCurrentRoom()->GetExit(exit_name);
	if (exit == nullptr) {
		cout << "\nThere is no exit named " << exit_name;
		return false;
	}
	return Lock(exit, key_name);
}

bool Player::Lock(Exit* exit, string key_name) {
	if (exit->IsLocked()) {
		cout << "\nThe " << exit->GetName() << " is already locked.";
		return false;
	}
	Item* key = GetFromInventory(key_name);
	if (key == nullptr) {
		cout << "\nYou don't have a " << key_name << ".";
		return false;
	}
	else {
		bool locked = exit->Lock(key);
		if (locked) {
			cout << "\nYou lock the " << exit->GetName() << " with the " << key_name;
		}
		else {
			cout << "\nThe " << key_name << " doesn't fit the " << exit->GetName();
		}
		return locked;
	}
}

//--------------------------------------
bool Player::Put(string item_name, string container_name) {
	Item* item_to_put = GetFromInventory(item_name);
	if (item_to_put == nullptr) {
		cout << "\nYou don't have a " << item_name << ".";
		return false;
	}

	Item* container = GetFromInventory(container_name);
	if (container == nullptr) {
		container = GetCurrentRoom()->GetItemByName(container_name);
		if (container == nullptr) {
			cout << "\nThere is no " << container_name << " here and you aren't holding it.";
			return false;
		}
	}

	if (container->GetItemType() != CONTAINER) {
		cout << "\nYou can't put anything in the " << container_name;
		return false;
	}

	if (!container->IsOpen()) {
		cout << "\nThe " << container_name << " is closed.";
		return false;
	}

	item_to_put->ChangeParent(container);
	cout << "\nYou put the " << item_name << " in the " << container_name;

	return true;
}

//--------------------------------------
bool Player::TakeFrom(string item_name, string container_name) {
	Item* item_container = nullptr;

	item_container = GetFromInventory(container_name);
	if (item_container == nullptr) {
		item_container = GetCurrentRoom()->GetItemByName(container_name);
	}
	if (item_container == nullptr) {
		cout << "\nThere is no " << container_name << " here and you aren't holding it.";
		return false;
	}
	if (item_container->GetItemType() != CONTAINER) {
		cout << "\nYou can't take anything from the " << container_name;
		return false;
	}

	if (!item_container->IsOpen()) {
		cout << "\nThe " << container_name << " is closed.";
		return false;
	}
			
	Item* item_to_take = GetFromContainer(item_name, item_container);
	if (item_to_take == nullptr) {
		cout << "\nThere is no " << item_name << " in the " << container_name;
		return false;
	}
	item_to_take->ChangeParent(this);
	cout << "\nYou take the " << item_name << " from the " << container_name;
	return true;
}

//--------------------------------------
void Player::Inventory() {
	if (contains.empty()) {
		cout << "\nYour inventory is empty.";
		return;
	}
	cout << "\nYou have this items in your inventory:";
	for (Entity* entity : contains) {
		cout << "\n- " << entity->GetName();
	}
}

//--------------------------------------
bool Player::Examine(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = GetFromInventory(item_name);
	if (item == nullptr) {
		item = current_room->GetItemByName(item_name);
	}

	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here and you aren't holding it.";
		return false;
	}
	
	item->Examine();
	return true;
}

//--------------------------------------
bool Player::Open(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = GetFromInventory(item_name);
	if (item == nullptr) {
		item = current_room->GetItemByName(item_name);
	}
	
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here and you aren't holding it.";
		return false;
	}
	if (item->GetItemType() != CONTAINER) {
		cout << "\nYou can't open the " << item_name;
		return false;
	}
	
	item->Open();
	return true;
}

//--------------------------------------
bool Player::Close(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = GetFromInventory(item_name);
	if (item == nullptr) {
		item = current_room->GetItemByName(item_name);
	}
	
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return false;
	}
	if (item->GetItemType() != CONTAINER) {
		cout << "\nYou can't close the " << item_name;
		return false;
	}
	
	item->Close();
	return true;
}

//--------------------------------------
bool Player::Read(string item_name) {
	Item* item = GetCurrentRoom()->GetItemByName(item_name);
	if (item == nullptr) {
		item = GetFromInventory(item_name);
		if (item == nullptr) {
			cout << "\nThere is no " << item_name << " here and you aren't holding it.";
			return false;
		}
	}
	if (item->GetItemType() != READABLE) {
		cout << "\nYou can't read a" << item_name;
		return false;
	}
	else {
		item->Examine();
		return true;
	}
}

//--------------------------------------
bool Player::Equip(string item_name) {
	if (equipped_weapon != nullptr) {
		cout << "\nYou already have something equipped.";
		return false;
	}

	Item* weapon = GetFromInventory(item_name);
	if (weapon == nullptr) {
		weapon = GetCurrentRoom()->GetItemByName(item_name);
	}
	if (weapon == nullptr) {
		cout << "\nThere is no " << item_name << " here and you aren't holding it.";
		return false;
	}

	if (weapon->GetItemType() != WEAPON) {
		cout << "\nYou can't equip the " << item_name;
		return false;
	}

	equipped_weapon = weapon;
	weapon->ChangeParent(this);
	cout << "\nYou equip the " << item_name;
	return true;
}

void Player::Unequip() {
	if (equipped_weapon != nullptr) {
		cout << "\nYou unequip the " << equipped_weapon->GetName();
		equipped_weapon = nullptr;
	}
	else {
		cout << "\nYou don't have anything equipped.";
	}
}

//--------------------------------------
bool Player::Attack(bool fatal_intent) {
	if (combat_target == nullptr) {
		cout << "\nWho are you attacking?";
		return false;
	}
	Attack(combat_target->GetName(), fatal_intent);
}

//Damage is randomly generated. Higher probability and higher damage with weapon
bool Player::Attack(string target_name, bool fatal_intent) {
	combat_target = GetCurrentRoom()->GetCreatureByName(target_name);

	if (combat_target == nullptr) {
		cout << "\nThere is no " << target_name << " here.";
		return false;
	}

	if (combat_target->GetHealthStatus() == UNCONSCIOUS) {
		combat_target->TakeDamage(FATAL_DAMAGE, true);
		return true;
	}

	if (equipped_weapon != nullptr) {
		DamageLevel damage = static_cast<DamageLevel>(rand() % 5);
		if (damage == NO_DAMAGE) {
			cout << "\nYou attack the " << combat_target->GetName() << " with the " << equipped_weapon->GetName() << " but miss.";
		}
		else {
			cout << "\nYou hit the " << combat_target->GetName() << " with the " << equipped_weapon->GetName();
			combat_target->TakeDamage(damage, fatal_intent);
		}
	}
	else {
		DamageLevel damage = static_cast<DamageLevel>(rand() % 2);
		if (damage == NO_DAMAGE) {
			cout << "\nYou attack the " << combat_target->GetName() << " but miss.";
			return true;
		}
		else {
			cout << "\nYou hit the " << combat_target->GetName() << " without any weapon.";
			combat_target->TakeDamage(damage, fatal_intent);
		}
	}

	if (!combat_target->IsHostile()) {
		combat_target->SetHostile(true);
		cout << "\nThe " << combat_target->GetName() << " is now mad at you!";
	}
}

//--------------------------------------
void Player::TakeDamage(DamageLevel damage, bool fatal_intent) {
	if (damage == NO_DAMAGE) {
		return;
	}

	int new_health_status = static_cast<int>(health_status) + static_cast<int>(damage);
	if (new_health_status > DEAD) {
		new_health_status = DEAD;
	}

	health_status = static_cast<HealthStatus>(new_health_status);

	if (health_status >= UNCONSCIOUS && !fatal_intent) {
		health_status = UNCONSCIOUS;
		cout << "\nYou fall unconscious.";
	}
	else if (health_status == UNCONSCIOUS && fatal_intent) {
		health_status = DEAD;
	}
	if (health_status >= DEAD) {
		health_status = DEAD;
		cout << "\nYou have died.";
		cout << "\nGame over.\nBetter luck next time!";
		cout << "\nDo you want to play again?";
	}
}

//--------------------------------------
void Player::Diagnose() {
	switch (health_status) {
	case HEALTHY:
		cout << "\nYou are in perfect health.";
		break;
	case LIGHTLY_WOUNDED:
		cout << "\nYou are a bit bruised.";
		break;
	case WOUNDED:
		cout << "\nYou have some cuts and bruises.";
		cout << "\nSeams you could use some rest.";
		break;
	case CRITICALLY_WOUNDED:
		cout << "\nYou are very hurt.";
		cout << "\nYou should find a place to rest soon.";
		break;
	case UNCONSCIOUS:
		cout << "\nYou are unconscious.";
		break;
	case DEAD:
		cout << "\nYou are dead.";
		break;
	}
}

//--------------------------------------
bool Player::Rest() {
	if (GetCurrentRoom()->GetHostileCreatures(this).size() > 0) {
		cout << "\nYou can't rest while there are hostile creatures in the room!";
		return false;
	}

	if (health_status == HEALTHY) {
		cout << "\nYou are already in perfect health.";
		resting = false;
		return false;
	}
	else if (health_status == UNCONSCIOUS || health_status == DEAD) {
		cout << "\nYou can't rest while you are unconscious or dead.";
		resting = false;
		return false;
	}
	else {
		resting = true;
		int new_health_status = static_cast<int>(health_status) - 1;
		if (new_health_status <= HEALTHY) {
			health_status = HEALTHY;
			resting = false;
			cout << "\nYou have fully recovered.";
		}
		else {
			health_status = static_cast<HealthStatus>(new_health_status);
			cout << "\nYou rest and recover a bit.";
			cout << "\nDo you want to keep resting?";
		}
		return true;
	}
}

bool Player::StopResting() {
	if (!resting) {
		cout << "\nYou aren't resting.";
		return false;
	}
	else {
		resting = false;
		cout << "\nYou stop resting.";
		Diagnose();
		return true;
	}
}