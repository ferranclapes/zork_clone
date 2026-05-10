#pragma once

#include <string>

#include "entity.h"

class Item;
class Exit;
class Creature;
class Player;
enum Directions;

class Room : public Entity {
public:
	//Methods-------------
	Room(const char* name, const char* description);

	void Look();

	Exit* GetExit(Directions dir);
	Item* GetItemByName(string item_name);
	Creature* GetCreatureByName(string creature_name);
	bool PlayerInRoom();
	Player* GetPlayer();
	//Atributes-------------
};