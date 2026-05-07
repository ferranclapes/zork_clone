#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "useful.h"
#include "world.h"


using namespace std;

int main()
{
    char kbchar;
    string player_input;
	vector<string> args;

	World world = World();


    cout << "Welcome to Zork!\n";
	cout << "--------------------\n";
	cout << "> ";

    while (1)
    {
        if (_kbhit() != 0) {
			kbchar = _getch();

			if (kbchar == '\b') {
				if (player_input.length() > 0) {
					player_input.pop_back();
					cout << "\b \b";	//Move back, print space to erase character, move back again
				}
			}
			else if (kbchar != '\r') {
				player_input += kbchar;
				cout << kbchar;
			}
			else {
				Tokenize(player_input, args);
			}
        }

		if (args.size() > 0 && (Same(args[0], "quit") || Same(args[0], "q"))) {
			break;
		}

		if (args.size() > 0) {
			world.ParseCommand(args);
		}

		if (args.size() > 0) {
			args.clear();
			player_input = "";
			cout << "\n> ";
		}
    }
}
