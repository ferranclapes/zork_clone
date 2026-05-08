#pragma once

#include "entity.h"

enum ItemType {
	MISC,
	WEAPON,
	READABLE,
	CONTAINER
};

class Item : public Entity {
public:
	// Methods-------------
	Item(const char* name, const char* description, Entity* parent, ItemType item_type);
	~Item();

	void Look();

	void Examine();
	void ListContents();
	void Open();
	void Close();

	// Attributes-------------
	ItemType item_type;
	bool is_open;
	bool is_locked;
};