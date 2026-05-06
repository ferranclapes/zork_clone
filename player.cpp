#include <iostream>
#include "player.h"
#include "room.h"
#include "exit.h"

//--------------------------------------
Player::Player(const char* name, const char* description, Room* room) : Creature(name, description, room) {
	type = PLAYER;
}

//--------------------------------------
Player::~Player() {}

//--------------------------------------
void Player::Look() {
	parent->Look();
}

//--------------------------------------
void Player::Go(Directions dir) {

	Room* current_room = GetCurrentRoom();

	for (list<Entity*>::const_iterator it = current_room->contains.begin(); it != current_room->contains.end(); ++it) {
		if ((*it)->type == EXIT) {
			Exit* exit = (Exit*)*it;

			if (exit->GetDirectionFrom(current_room) == dir) {
				if (!exit->is_locked) {
					parent = exit->GetDestinationFrom(current_room);
					cout << "\nYou go to the " << DirectionToString(dir);
					Look();
				}
				else {
					cout << "\nThe " << exit->name << " is locked";
				}
				return;
			}
		}
	}
	cout << "\nThere is no exit to the " << DirectionToString(dir);
}