#include <iostream>
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
}