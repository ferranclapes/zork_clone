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
void Player::Drop(string item_name) {
	Item* item_to_drop = nullptr;
	for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
		Item* item = (Item*)*it;
		if (Same(item->name, item_name)) {
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
	if (!exit->is_locked) {
		cout << "\nThe " << exit->name << " is not locked.";
		return;
	}
	for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
		Item* item = (Item*)*it;
		if (Same(item->name, key_name)) {
			exit->is_locked = false;
			cout << "\nYou unlock the " << exit->name << " with the " << key_name;
			return;
		}
	}
}

//--------------------------------------
void Player::Put(string item_name, string container_name) {
	Item* item_to_put = nullptr;
	for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
		Item* item = (Item*)*it;
		if (Same(item->name, item_name)) {
			item_to_put = item;
			break;
		}
	}
	if (item_to_put == nullptr) {
		cout << "\nYou don't have a " << item_name << ".";
		return;
	}
	
	//First try finding container in the inventory
	for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
		Item* container = (Item*)*it;
		if (Same(container->GetName(), container_name)) {
			if (container->item_type != CONTAINER) {
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
	for (list<Entity*>::const_iterator it = current_room->contains.begin(); it != current_room->contains.end(); ++it) {
		if ((*it)->type == ITEM) {
			Item* container = (Item*)*it;
			if (Same(container->GetName(), container_name)) {
				if (container->item_type != CONTAINER) {
					cout << "\nYou can't put anything in the " << container_name;
					return;
				}
				if (!container->is_open) {
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
	for (list<Item*>::const_iterator it = inventory.begin(); it != inventory.end(); ++it) {
		Item* container = (Item*)*it;
		if (Same(container->GetName(), container_name)) {
			if (container->item_type != CONTAINER) {
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
		for (list<Entity*>::const_iterator it = current_room->contains.begin(); it != current_room->contains.end(); ++it) {
			if ((*it)->type == ITEM) {
				Item* container = (Item*)*it;
				if (Same(container->GetName(), container_name)) {
					if (container->item_type != CONTAINER) {
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
			
	for (list<Entity*>::const_iterator it2 = item_container->contains.begin(); it2 != item_container->contains.end(); ++it2) {
		if ((*it2)->type == ITEM) {
			Item* item = (Item*)*it2;
			if (Same(item->GetName(), item_name)) {
				item->ChangeParent(this);
				inventory.push_back(item);
				item_container->contains.remove((Entity*)item);
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

//--------------------------------------
void Player::Open(string item_name) {
	Room* current_room = GetCurrentRoom();

	Item* item = current_room->GetItemByName(item_name);
	
	if (item == nullptr) {
		cout << "\nThere is no " << item_name << " here.";
		return;
	}
	if (item->item_type != CONTAINER) {
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
	if (item->item_type != CONTAINER) {
		cout << "\nYou can't close the " << item_name;
		return;
	}
	
	item->Close();
}
