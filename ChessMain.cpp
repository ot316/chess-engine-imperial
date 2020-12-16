#include"ChessBoard.h"

#include<iostream>

using std::cout;
using std::cin;

int main() {
	ChessBoard cb;
	cout << "\n\t";
	char end_pos_[4], start_pos_[4], start_pos[4], end_pos[2];
	bool i = false;
	while (true) {
		int n;
		for (n = 0; n < 5; n++)
			cout << "\n\n\n\n\n\n\n\n\n\n\t";
		cout << "==================================\n\t";
		cout << "Welcome to the Virtual Chess Board\n\t";
		cout << "==================================\n\n\t";
		strncpy(start_pos_, start_pos, 2);
		strncpy(end_pos_, end_pos, 2);
		if (i != 0) {
			cb.submitMove(start_pos_, end_pos_);
		    cb.displayBoard();
		}
		else {
			cb.displayBoard();
			cout << "\tPlease enter the coordinates of your move,\n\tfor example 'D2 D4'. white goes first.\n\n";
		}
		i = true;
		cout << "\t";
		cin >> start_pos;
		cin >> end_pos;
		cout << "\n\t";
	}

	return 0;
}
