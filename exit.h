#pragma once

#include "entity.h"
#include "useful.h"

class Room;

class Exit : public Entity {
public:
	//Methods-------------
	Exit(const char* name, Directions direction, Directions opposite_direction, Room* source, Room* destination, bool is_one_way);
	~Exit();

	void Look(Room* current_room);
	Directions GetDirectionFrom(Room* current_room);
	Room* GetDestinationFrom(Room* current_room);

	//Attributes-------------
	Directions direction;
	Directions opposite_direction;
	Room* source;
	Room* destination;

	bool is_locked = false;
	bool is_one_way = false;

};