#pragma once

#include <list>
#include "entity.h"
#include "useful.h"

using namespace std;

class Room;
class Item;

class Exit : public Entity {
public:
	//Methods-------------
	Exit(const char* name, Directions direction, Directions opposite_direction, Room* source, Room* destination, bool is_one_way, bool is_locked);
	~Exit();

	void Look(Room* current_room);
	Directions GetDirectionFrom(Room* current_room);
	Room* GetDestinationFrom(Room* current_room);
	void AddKey(Item* key);

	bool IsLocked() { return is_locked; }
	void Unlock();
	void Lock();
	//Attributes-------------
private:
	Directions direction;
	Directions opposite_direction;
	Room* source;
	Room* destination;
	list<Item*> keys;

	bool is_locked = false;
	bool is_one_way = false;

};