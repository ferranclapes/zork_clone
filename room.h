#pragma once

#include "entity.h"

class Room : public Entity {
public:
	//Methods-------------
	Room(const char* name, const char* description);
	~Room();
	void Look();


	//Atributes-------------
};