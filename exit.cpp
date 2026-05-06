#include <iostream>
#include "exit.h"
#include "room.h"

//--------------------------------------
Exit::Exit(const char* name, Directions direction, Directions opposite_direction, Room* source, Room* destination, bool is_one_way) : Entity(name, "", source) {
	this->type = EXIT;
	this->direction = direction;
	this->opposite_direction = opposite_direction;
	this->source = source;
	this->destination = destination;
	this->is_one_way = is_one_way;

	if (!is_one_way) {
		destination->contains.push_back(this);
	}
}

//--------------------------------------
Exit::~Exit() {}

//--------------------------------------
void Exit::Look(Room* current_room) {
	string dir;
	if (current_room == source) {
		dir = DirectionToString(direction);
	}
	else if (current_room == destination) {
		dir = DirectionToString(opposite_direction);
	}
	
	if (!is_locked) {
		cout << "\nYou see a " << name << " to the " << dir;
	}
	else {
		cout << "\nYou see a locked " << name << " to the " << dir;
	}
}

//--------------------------------------
Directions Exit::GetDirectionFrom(Room* current_room) {
	if (current_room == source) {
		return direction;
	}
	else if (current_room == destination) {
		return opposite_direction;
	}
	else {
		return ERROR;
	}
}

//--------------------------------------
Room* Exit::GetDestinationFrom(Room* current_room) {
	if (current_room == source) {
		return destination;
	}
	else if (current_room == destination) {
		return source;
	}
	else {
		return NULL;
	}
}