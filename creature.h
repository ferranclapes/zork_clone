#pragma once

#include <list>
#include <string>
#include "entity.h"


class Room;
class Item;
class Exit;
enum Directions;

enum HealthStatus {
	HEALTHY,
	LIGHTLY_WOUNDED,
	WOUNDED,
	CRITICALLY_WOUNDED,
	UNCONSCIOUS,
	DEAD
};

enum DamageLevel {
	NO_DAMAGE,
	LIGHT_DAMAGE,
	MEDIUM_DAMAGE,
	HEAVY_DAMAGE,
	FATAL_DAMAGE
};

using namespace std;

class Creature : public Entity {
public:
	//Methods-------------
	Creature(const char* name, const char* description, Room* room, bool is_hostile);

	virtual void Update();

	virtual void Look();
	virtual bool Go(Directions dir);

	virtual bool Take(string item_name);
	virtual bool Unlock(Exit* exit, string key_name);
	virtual bool Lock(Exit* exit, string key_name);
	Item* GetFromInventory(string item_name);
	Item* GetFromContainer(string item_name, Item* container);

	virtual bool Equip(string item_name);
	virtual void Unequip();

	Room* GetCurrentRoom();

	bool IsAlive();
	bool IsUnconscious() { return health_status == UNCONSCIOUS; }

	HealthStatus GetHealthStatus() { return health_status; }

	virtual bool StartResting();
	virtual bool Rest();
	virtual bool StopResting();
	bool IsResting() { return resting; }

	void Attack();
	virtual void TakeDamage(DamageLevel damage, bool fatal_intent);

	bool IsHostile() { return is_hostile; }
	void SetHostile(bool is_hostile) { this->is_hostile = is_hostile; }
	Creature* GetCombatTarget() { return combat_target; }
	//Atributes-------------
protected:
	HealthStatus health_status = HEALTHY;
	bool resting = false;
	bool is_hostile;
	Creature* combat_target = nullptr;
	Item* equipped_weapon = nullptr;
};