#include <iostream>
#include "exit.h"
#include "room.h"
#include "item.h"

//--------------------------------------
Exit::Exit(const char* name, const char* description, Directions direction, Directions opposite_direction, Room* source, Room* destination, bool is_locked) : Entity(name, description, source) {
	this->type = EXIT;
	this->direction = direction;
	this->opposite_direction = opposite_direction;
	this->source = source;
	this->destination = destination;
	this->is_locked = is_locked;

	destination->AddContainedEntity(this);
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

	
	if (is_locked) {
		cout << "\nYou see a closed " << description << " going " << dir << ". It seems locked.";
	}
	else {
		cout << "\nYou see a " << description << " going " << dir << ".";
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
void Exit::SetKey(Item* key) {
	this->key = key;
}

//--------------------------------------
bool Exit::Unlock(Item* key) {
	if (this->key == key) {
		is_locked = false;
		return true;
	}
	return false;
}

bool Exit::Lock(Item* key) {
	if (this->key == key) {
		is_locked = true;
		return true;
	}
	return false;
}