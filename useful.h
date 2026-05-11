#pragma once

#include <string>
#include <vector>

class Item;

using namespace std;

enum Directions {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	UP,
	DOWN,
	ERROR
};


struct DialogueLine {
	string text = "";
	Item* required_item = nullptr;	// The item must be in the creature's inventory to advance to next line
	Item* item_to_give = nullptr;	// The item will be given when advanced to this line
	int next_line_index = -1;
};

void Tokenize(const string& line, vector<string>& arguments);
bool Same(const string& a, const string& b);
bool Same(const string& a, const char* b);
bool Same(const char* a, const string& b);
string DirectionToString(Directions dir);
Directions StringToDirection(string str);