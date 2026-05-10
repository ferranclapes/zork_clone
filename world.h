#pragma once

#include <list>
#include <vector>
#include <string>
#include <chrono>

#define UPDATE_FREQUENCY 0.5f

using namespace std;

class Entity;
class Player;

class World {
public:
	//Methods-------------
	World();
	~World();

	bool Update(vector<string> args);
	bool ParseCommand(vector<string> args);

	//Atributes-------------
private:
	chrono::steady_clock::time_point start_time;
	list<Entity*> entities;
	Player* player;
};