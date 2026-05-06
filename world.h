#pragma once

#include <list>
#include <vector>
#include <string>

class Entity;
class Player;

using namespace std;

class World {
public:
	//Methods-------------
	World();
	~World();

	void ParseCommand(vector<string> args);

	//Atributes-------------
	list<Entity*> entities;
	Player* player;
};