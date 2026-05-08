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
Item::~Item() {}

//--------------------------------------
void Item::Look() {
	switch (item_type) {
	case CONTAINER:
		if (is_open) {
			cout << "\nThere is an open " << name << " here.";
			if (!contains.empty()) {
				cout << " It contains:";
				for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
					if ((*it)->type == ITEM) {
						Item* item = (Item*)(*it);
						cout << "\n - " << item->GetName();
					}
				}
			}
		}
		else {
			cout << "\nThere is a closed " << name << " here.";
		}
		break;
	default:
		cout << "\nYou see a " << name;
		break;
	}
}

//--------------------------------------
void Item::Examine() {
	cout << "\n" << description;
	if (item_type == CONTAINER) {
		ListContents();
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
	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == ITEM) {
			Item* item = (Item*)(*it);
			cout << "\n - " << item->GetName();
		}
	}
}

//--------------------------------------
void Item::Open() {
	if (item_type != CONTAINER) {
		cout << "\nYou can't open the " << name;
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
	cout << "\nYou open the " << name;
	ListContents();
}

void Item::Close() {
	if (item_type != CONTAINER) {
		cout << "\nYou can't close the " << name;
		return;
	}
	if (!is_open) {
		cout << "\nThe " << name << " is already closed.";
		return;
	}
	is_open = false;
	cout << "\nYou close the " << name;
}