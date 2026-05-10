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

	cout << "Welcome to Zork!";
	cout << "\n--------------------";

	World world = World();

	cout << "\n\n> ";

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

		bool player_alive = world.Update(args);

		if (!player_alive) {
			int play_again = world.GameOver(args);
			if (play_again == 1) {
				world.ResetWorld();
			}
			else if (play_again == 2) {
				break;
			}
		}

		if (args.size() > 0) {
			args.clear();
			player_input = "";
			cout << "\n\n> ";
		}
    }
}
