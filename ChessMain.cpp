#include"ChessBoard.h"
#include<iostream>

using std::cout;
using std::cin;

int main() {
	ChessBoard cb;

	char input[256], *start_pos, *end_pos;
	bool first_move = true;

	while (true) {
		cout << "\033[2J\033[1;1H\n\t";
		cout << " ——————————————————————————————————\n\t";
		cout << " Welcome to the Virtual Chess Board\n\t";
		cout << " ——————————————————————————————————\n\n\t";

		cb.displayBoard();

		if (first_move)
			cout << "\tPlease enter the coordinates of your move,\n\tfor example 'D2 D4'. white goes first.\n\n";
			
		first_move = false;

		if (cb.inPlay())
			cout << "\t" << ">> ";

		cin.getline(input, 256);
		start_pos = strtok (input, " ,.-");
		end_pos = strtok (NULL, " ,.-");

		if (start_pos != nullptr) {
			if (!strcmp(start_pos, "Resign") || !strcmp(start_pos, "resign")) {
				cb.resign();
				continue;
			}

			if (!strcmp(start_pos, "Reset") || !strcmp(start_pos, "reset")) {
				cb.resetBoard();
				first_move = true;
				continue;
			}
			if (end_pos != nullptr)	
				cb.submitMove(start_pos, end_pos);
			}
		}

	return 0;
}
