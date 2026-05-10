#include <iostream>
#include "exit.h"
#include "room.h"
#include "item.h"

//--------------------------------------
Exit::Exit(const char* name, Directions direction, Directions opposite_direction, Room* source, Room* destination, bool is_one_way, bool is_locked) : Entity(name, "", source) {
	this->type = EXIT;
	this->direction = direction;
	this->opposite_direction = opposite_direction;
	this->source = source;
	this->destination = destination;
	this->is_one_way = is_one_way;
	this->is_locked = is_locked;

	if (!is_one_way) {
		destination->AddContainedEntity(this);
	}
}

//--------------------------------------
Exit::~Exit() {
	if (destination != nullptr)
		destination->RemoveContainedEntity(this);
	if (parent != nullptr)
		parent->RemoveContainedEntity(this);
}

void Exit::RemoveDestination() {
	if (destination != nullptr) {
		destination = nullptr;
	}
}

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

//--------------------------------------
void Exit::AddKey(Item* key) {
	this->keys.push_back(key);
}

//--------------------------------------
void Exit::Unlock() {
	is_locked = false;
}

void Exit::Lock() {
	is_locked = true;
}