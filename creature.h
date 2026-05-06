#pragma once

#include <list>
#include "entity.h"


class Room;
class Item;

using namespace std;

class Creature : public Entity {
public:
	//Methods-------------
	Creature(const char* name, const char* description, Room* room);
	~Creature();
	virtual void Look();
	virtual void Go();
	Room* GetCurrentRoom();
	//Atributes-------------
	int hp;
	list<Item*> inventory;
};