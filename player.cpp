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
	GetCurrentRoom()->Look();
}

//--------------------------------------
void Player::Go(Directions dir) {

	Room* current_room = GetCurrentRoom();

	Exit* exit = current_room->GetExit(dir);

	if (exit == nullptr) {
		cout << "\nThere is no exit to the " << DirectionToString(dir);
		return;
	}
	
	if (exit->IsLocked()) {
		cout << "\nThe " << exit->GetName() << " is locked";
		return;
	}

	ChangeParent(exit->GetDestinationFrom(current_room));
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
	current_room->RemoveContainedEntity(item);
	cout << "\nYou take the " << item_name;
}

//--------------------------------------
void Player::Drop(string item_name) {
	Item* item_to_drop = nullptr;
	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (Same(item->GetName(), item_name)) {
			item_to_drop = item;
			inventory.remove(item_to_drop);
			item->ChangeParent(GetCurrentRoom());
			cout << "\nYou drop the " << item_name;
			return;
		}
	}
	cout << "\nYou don't have a " << item_name << ".";
}

//--------------------------------------
void Player::Unlock(Directions dir, string key_name) {
	Room* current_room = GetCurrentRoom();
	Exit* exit = current_room->GetExit(dir);
	if (exit == nullptr) {
		cout << "\nThere is no exit to the " << DirectionToString(dir);
		return;
	}
	if (!exit->IsLocked()) {
		cout << "\nThe " << exit->GetName() << " is not locked.";
		return;
	}
	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (Same(item->GetName(), key_name)) {
			exit->Unlock();
			cout << "\nYou unlock the " << exit->GetName() << " with the " << key_name;
			return;
		}
	}
}

//--------------------------------------
void Player::Put(string item_name, string container_name) {
	Item* item_to_put = nullptr;
	for (Entity* entity : inventory) {
		Item* item = (Item*)entity;
		if (Same(item->GetName(), item_name)) {
			item_to_put = item;
			break;
		}
	}
	if (item_to_put == nullptr) {
		cout << "\nYou don't have a " << item_name << ".";
		return;
	}
	
	//First try finding container in the inventory
	for (Entity* entity : inventory) {
		Item* container = (Item*)entity;
		if (Same(container->GetName(), container_name)) {
			if (container->GetItemType() != CONTAINER) {
				cout << "\nYou can't put anything in the " << container_name;
				return;
			}
			item_to_put->ChangeParent(container);
			inventory.remove(item_to_put);
			cout << "\nYou put the " << item_name << " in the " << container_name;
			return;
		}
	}

	//Then try finding container in the room
	Room* current_room = GetCurrentRoom();
	for (Entity* entity : current_room->GetContains()) {
		if (entity->GetType() == ITEM) {
			Item* container = (Item*)entity;
			if (Same(container->GetName(), container_name)) {
				if (container->GetItemType() != CONTAINER) {
					cout << "\nYou can't put anything in the " << container_name;
					return;
				}
				if (!container->IsOpen()) {
					cout << "\nThe " << container_name << " is closed.";
					return;
				}
				item_to_put->ChangeParent(container);
				inventory.remove(item_to_put);
				cout << "\nYou put the " << item_name << " in the " << container_name;
				return;
			}
		}
	}

}

//--------------------------------------
void Player::TakeFrom(string item_name, string container_name) {
	Item* item_container = nullptr;
	//First try finding container in the inventory
	for (Entity* entity : inventory) {
		Item* container = (Item*)entity;
		if (Same(container->GetName(), container_name)) {
			if (container->GetItemType() != CONTAINER) {
				cout << "\nYou can't take anything from the " << container_name;
				return;
			}
			item_container = container;
			break;
		}
	}

	//Then try finding container in the room
	if (item_container == nullptr) {
		Room* current_room = GetCurrentRoom();
		for (Entity* entity : current_room->GetContains()) {
			if (entity->GetType() == ITEM) {
				Item* container = (Item*)entity;
				if (Same(container->GetName(), container_name)) {
					if (container->GetItemType() != CONTAINER) {
						cout << "\nYou can't take anything from the " << container_name;
						return;
					}
					item_container = container;
					break;
				}
			}
		}
	}

	if (item_container == nullptr) {
		cout << "\nThere is no " << container_name << " here and you aren't holding it.";
		return;
	}
			
	for (Entity* entity : item_container->GetContains()) {
		if (entity->GetType() == ITEM) {
			Item* item = (Item*)entity;
			if (Same(item->GetName(), item_name)) {
				item->ChangeParent(this);
				inventory.push_back(item);
				item_container->RemoveContainedEntity(item);
				cout << "\nYou take the " << item_name << " from the " << container_name;
				return;
			}
		}
	}
	cout << "\nThere is no " << item_name << " in the " << container_name;
	return;
}

//--------------------------------------
void Player::Inventory() {
	if (inventory.empty()) {
		cout << "\nYour inventory is empty.";
		return;
	}
	cout << "\nYou have this items in your inventory:";
	for (Entity* entity : inventory) {
		cout << "\n- " << entity->GetName();
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

//--------------------------------------
void Player::Open(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = current_room->GetItemByName(item_name);
	
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return;
	}
	if (item->GetItemType() != CONTAINER) {
		cout << "\nYou can't open the " << item_name;
		return;
	}
	
	item->Open();
}

//--------------------------------------
void Player::Close(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = current_room->GetItemByName(item_name);
	
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return;
	}
	if (item->GetItemType() != CONTAINER) {
		cout << "\nYou can't close the " << item_name;
		return;
	}
	
	item->Close();
}
