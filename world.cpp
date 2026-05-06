#include "world.h"
#include "room.h"
#include "exit.h"
#include "player.h"
#include "useful.h"

//--------------------------------------
World::World() {

	Room* room1 = new Room("Room 1", "This is a room called Room 1");
	Room* room2 = new Room("Room 2", "This is a room called Room 2");

	Exit* exit1 = new Exit("Little Path", EAST, WEST, room1, room2, false);

	player = new Player("Player", "This is the player", room1);

	entities.push_back(room1);
	entities.push_back(room2);

	entities.push_back(exit1);

	entities.push_back(player);
}

//--------------------------------------
World::~World() {
	for (list<Entity*>::const_iterator it = entities.begin(); it != entities.end(); ++it) {
		delete* it;
	}
}

//--------------------------------------
void World::ParseCommand(vector<string> args) {
	switch (args.size()) {
	case 1:
		if (Same(args[0], "look")) {
			player->Look();
			break;
		}
		if (Same(args[0], "east") || Same(args[0], "west") || Same(args[0], "north") || Same(args[0], "south")
			|| Same(args[0], "e") || Same(args[0], "w") || Same(args[0], "n") || Same(args[0], "s")) {
			player->Go(StringToDirection(args[0]));
			break;
		}

	case 2:
		if (Same(args[0], "go")) {
			player->Go(StringToDirection(args[1]));
			break;
		}
	}
}