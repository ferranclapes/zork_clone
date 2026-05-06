#include <iostream>
#include "room.h"
#include "exit.h"

using namespace std;

//--------------------------------------
Room::Room(const char* name, const char* description) : Entity(name, description, NULL) {
	type = ROOM;
}

//--------------------------------------
Room::~Room() {}

//--------------------------------------
void Room::Look() {
	cout << "\n" << name;
	cout << "\n" << description;

	for (list<Entity*>::const_iterator it = contains.begin(); it != contains.end(); ++it) {
		if ((*it)->type == EXIT) {
			Exit* exit = (Exit*)*it;
			exit->Look(this);

		}
	}
}
