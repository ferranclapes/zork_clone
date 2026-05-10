#pragma once

#include <string>

#include "entity.h"

class Item;
class Exit;
enum Directions;

class Room : public Entity {
public:
	//Methods-------------
	Room(const char* name, const char* description);

	void Look();

	Exit* GetExit(Directions dir);
	Item* GetItemByName(string item_name);
	bool PlayerInRoom();
	//Atributes-------------
};