#pragma once

#include <list>
#include <string>
#include "entity.h"


class Room;
class Item;
enum Directions;

using namespace std;

class Creature : public Entity {
public:
	//Methods-------------
	Creature(const char* name, const char* description, Room* room);

	virtual void Look();
	virtual void Go(Directions dir);

	virtual void Take(string item_name);
	virtual void Unlock(Directions dir, string key_name);

	Room* GetCurrentRoom();

	bool IsAlive();
	//Atributes-------------
protected:
	int hp;
	list<Item*> inventory;
};