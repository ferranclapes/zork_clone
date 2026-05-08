#pragma once

#include <list>
#include <string>
#include "creature.h"
#include "useful.h"

using namespace std;

class Player : public Creature {
public:
	//Methods-------------
	Player(const char* name, const char* description, Room* room);
	~Player();

	void Look();
	void Go(Directions dir);
	void Take(string item_name);
	void Drop(string item_name);
	void Unlock(Directions dir, string key_name);
	void Put(string item_name, string container_name);
	void TakeFrom(string item_name, string container_name);

	void Inventory();
	void Examine(string item_name);
	void Open(string container_name);
	void Close(string container_name);
	//Atributes-------------
};