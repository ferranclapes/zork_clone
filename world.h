#pragma once

#include <list>
#include <vector>
#include <string>

#define UPDATE_FREQUENCY 0.5f

using namespace std;

enum CommandReturnValue {
	VALID_COMMAND,
	WRONG_PARAMETERS,
	INVALID_COMMAND
};

class Entity;
class Player;

class World {
public:
	//Methods-------------
	World();
	~World();

	void InitializeWorld();
	void ResetWorld();

	bool Update(vector<string> args);
	CommandReturnValue ParseCommand(vector<string> args);

	int GameOver(vector<string> args);

	//Atributes-------------
private:
	list<Entity*> entities;
	Player* player;
};