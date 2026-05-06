#include "useful.h"

//--------------------------------------
void Tokenize(const string& line, vector<string>& arguments) {

	const char* str = line.c_str();

	 do{
		const char* word_start = str;

		while (*str != ' ' && *str) {
			str++;
		}

		arguments.push_back(string(word_start, str));
	 } while (*str++ != 0);
}

//--------------------------------------
bool Same(const string& a, const string& b) {
	return _stricmp(a.c_str(), b.c_str()) == 0;
}

bool Same(const string& a, const char* b) {
	return _stricmp(a.c_str(), b) == 0;
}

bool Same(const char* a, const string& b) {
	return _stricmp(a, b.c_str()) == 0;
}

//--------------------------------------
string DirectionToString(Directions dir) {
	switch (dir) {
	case NORTH:
		return "north";
	case EAST:
		return "east";
	case SOUTH:
		return "south";
	case WEST:
		return "west";
	default:
		return "";
	}
}

Directions StringToDirection(const string str) {
	if (Same(str, "north") || Same(str, "n")) {
		return NORTH;
	}
	else if (Same(str, "east") || Same(str, "e")) {
		return EAST;
	}
	else if (Same(str, "south") || Same(str, "s")) {
		return SOUTH;
	}
	else if (Same(str, "west") || Same(str, "w")) {
		return WEST;
	}
	else {
		return ERROR; //Default value
	}
}