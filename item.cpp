#include <iostream>
#include <list>
#include "item.h"

//--------------------------------------
Item::Item(const char* name, const char* description, Entity* parent, ItemType item_type) : Entity(name, description, parent) {
	this->type = ITEM;
	this->item_type = item_type;

	is_locked = false;
	is_open = false;
}

//--------------------------------------
void Item::Look() {
	switch (item_type) {
	case CONTAINER:
		if (is_open) {
			cout << "\nThere is an open " << name << " here.";
			if (!contains.empty()) {
				cout << " It contains:";
				for (Entity* entity : contains) {
					cout << "\n - " << entity->GetName();
				}
			}
		}
		else {
			cout << "\nThere is a closed " << name << " here.";
		}
		break;
	default:
		cout << "\nYou see a " << name << ".";
		break;
	}
}

//--------------------------------------
void Item::Examine() {
	if (item_type == READABLE) {
		cout << "\nYou read the " << name << ":";
	}
	cout << "\n" << description;
	if (item_type == CONTAINER) {
		ListContents();
	}
	else if (item_type == LIGHT_SOURCE) {
		if (is_open) {
			cout << "\nIt's turned on.";
		}
		else {
			cout << "\nIt's turned off.";
		}
	}
}

//--------------------------------------
void Item::ListContents() {
	if (item_type != CONTAINER) {
		cout << "\nThe " << name << " is not a container.";
		return;
	}
	if (!is_open) {
		cout << "\nIt's closed.";
		return;
	}
	if (contains.empty()) {
		cout << "\nIt's empty.";
		return;
	}
	cout << "\nIt contains:";
	for (Entity* entity : contains) {
		if (entity->GetType() == ITEM) {
			Item* item = (Item*)entity;
			cout << "\n - " << item->GetName();
		}
	}
}

//--------------------------------------
void Item::Open() {
	if (item_type != CONTAINER) {
		cout << "\nYou can't open the " << name << ".";
		return;
	}
	if (is_open) {
		cout << "\nThe " << name << " is already open.";
		return;
	}
	if (is_locked) {
		cout << "\nThe " << name << " is locked.";
		return;
	}
	is_open = true;
	cout << "\nYou open the " << name << ".";
	ListContents();
}

void Item::Close() {
	if (item_type != CONTAINER) {
		cout << "\nYou can't close the " << name << ".";
		return;
	}
	if (!is_open) {
		cout << "\nThe " << name << " is already closed.";
		return;
	}
	is_open = false;
	cout << "\nYou close the " << name << ".";
}

//--------------------------------------
bool Item::TurnOn() {
	if (item_type != LIGHT_SOURCE || is_open) {
		return false;
	}
	is_open = true;
	return true;
}

bool Item::TurnOff() {
	if (item_type != LIGHT_SOURCE || !is_open) {
		return false;
	}
	is_open = false;
	return true;
}