#include "creature.h"
#include "room.h"

//--------------------------------------
Creature::Creature(const char* name, const char* description, Room* room) : Entity(name, description, (Entity*) room) {
	type = CREATURE;
	hp = 1;
}

//--------------------------------------
Creature::~Creature() {}

//--------------------------------------
void Creature::Look() {}

//--------------------------------------
void Creature::Go() {
}

//--------------------------------------
Room* Creature::GetCurrentRoom() {
	return (Room*)parent;
}
