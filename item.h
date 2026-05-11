#pragma once

#include "entity.h"

enum ItemType {
	MISC,
	WEAPON,
	READABLE,
	CONTAINER,
	LIGHT_SOURCE
};

class Item : public Entity {
public:
	// Methods-------------
	Item(const char* name, const char* description, Entity* parent, ItemType item_type);

	void Look();
	void Examine();

	void ListContents();
	void Open();
	void Close();

	ItemType GetItemType() { return item_type; }

	bool IsOpen() { return is_open; }
	bool IsLocked() { return is_locked; }

	bool TurnOn();
	bool TurnOff();
	bool IsTurnedOn() { return is_open; }
	// Attributes-------------
private:
	ItemType item_type;
	bool is_open;	//Used by CONTAINER and LIGHT_SOURCE
	bool is_locked;
};