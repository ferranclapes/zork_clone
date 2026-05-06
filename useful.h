#pragma once

#include <string>
#include <vector>

using namespace std;

enum Directions {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	ERROR
};

void Tokenize(const string& line, vector<string>& arguments);
bool Same(const string& a, const string& b);
bool Same(const string& a, const char* b);
bool Same(const char* a, const string& b);
string DirectionToString(Directions dir);
Directions StringToDirection(string str);