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

	void Look();
	bool Go(Directions dir);
	bool Take(string item_name);
	bool Drop(string item_name);
	bool Unlock(Directions dir, string key_name);
	bool Put(string item_name, string container_name);
	bool TakeFrom(string item_name, string container_name);

	void Inventory();
	bool Examine(string item_name);
	bool Open(string container_name);
	bool Close(string container_name);

	bool Equip(string item_name);
	void Unequip();

	bool Attack(bool fatal_intent);
	bool Attack(string target_name, bool fatal_intent);
	void TakeDamage(DamageLevel damage, bool fatal_intent);
	//Atributes-------------
};