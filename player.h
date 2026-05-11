#pragma once

#include <string>
#include "creature.h"
#include "useful.h"

class Exit;

class Player : public Creature {
public:
	//Methods-------------
	Player(const char* name, const char* description, Room* room);

	void Look();
	bool Go(Directions dir);
	bool Take(string item_name);
	bool Take(Item* item);
	bool Drop(string item_name);
	bool Put(string item_name, string container_name);
	bool TakeFrom(string item_name, string container_name);
	bool Give(string item_name, string creature_name);

	void Inventory();
	bool Examine(string item_name);
	bool Open(string container_name);
	bool Close(string container_name);
	bool Read(string item_name);

	bool Unlock(Directions dir, string key_name);
	bool Unlock(string exit_name, string key_name);
	bool Unlock(Exit* exit, string key_name);

	bool Lock(Directions dir, string key_name);
	bool Lock(string exit_name, string key_name);
	bool Lock(Exit* exit, string key_name);

	bool Equip(string item_name);
	void Unequip();

	bool TurnOn(string item_name);
	bool TurnOff(string item_name);

	bool Attack(bool fatal_intent);
	bool Attack(string target_name, bool fatal_intent);
	void TakeDamage(DamageLevel damage, bool fatal_intent);

	void Diagnose();
	bool Rest();
	bool StopResting();

	bool Talk(string creature_name);
	//Atributes-------------
};