#include"ChessBoard.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	cout << '\n';

	cb.submitMove("D7", "D6");
	cout << '\n';

	cb.submitMove("D4", "H6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cout << '\n';

	cb.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("F8", "B4");
	cout << '\n';

	cb.submitMove("F1", "D3");
	cb.submitMove("B4", "C3");
	cout << '\n';

	cb.submitMove("B2", "C3");
	cb.submitMove("H7", "H6");
	cout << '\n';

	cb.submitMove("C1", "A3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D1", "E2");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("D3", "E4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E4", "D3");
	cb.submitMove("B7", "B6");
	cout << '\n';

	cb.submitMove("E2", "E6");
	cb.submitMove("F7", "E6");
	cout << '\n';

	cb.submitMove("D3", "G6");
	cout << '\n';

	cout << "==================================\n";
	cout << "Marjanovic vs Ivan Zhivanov (1946)\n";
	cout << "==================================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("C7", "C5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("B8", "C6");
	cout << '\n';

	cb.submitMove("G1", "E2");
	cb.submitMove("G7", "G6");
	cout << '\n';

	cb.submitMove("D2", "D3");
	cb.submitMove("F8", "G7");
	cout << '\n';

	cb.submitMove("C1", "E3");
	cb.submitMove("C6", "D4");
	cout << '\n';

	cb.submitMove("G2", "G3");
	cb.submitMove("D4", "F3");
	cout << '\n';

	cout << "================\n";
	cout << "3 Move checkmate\n";
	cout << "================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("F7", "F5");
	cout << '\n';

	cb.submitMove("E4", "F5");
	cb.submitMove("G7", "G5");
	cout << '\n';

	cb.submitMove("D1", "H5");
	cout << '\n';

	cout << "================\n";
	cout << "4 Move Checkmate\n";
	cout << "================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E3");
	cb.submitMove("E7", "E5");
	cout << '\n';

	cb.submitMove("D1", "H5");
	cb.submitMove("B8", "C6");
	cout << '\n';

	cb.submitMove("F1", "C4");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("H5", "F7");
	cout << '\n';

	cout << "=======================\n";
	cout << "Fastest known stalemate\n";
	cout << "=======================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("C2", "C4");
	cb.submitMove("H7", "H5");
	cout << '\n';

	cb.submitMove("H2", "H4");
	cb.submitMove("A7", "A5");
	cout << '\n';

	cb.submitMove("D1", "A4");
	cb.submitMove("A8", "A6");
	cout << '\n';

	cb.submitMove("A4", "A5");
	cb.submitMove("A6", "H6");
	cout << '\n';

	cb.submitMove("A5", "C7");
	cb.submitMove("F7", "F6");
	cout << '\n';

	cb.submitMove("C7", "D7");
	cb.submitMove("E8", "F7");
	cout << '\n';

	cb.submitMove("D7", "B7");
	cb.submitMove("D8", "D3");
	cout << '\n';

	cb.submitMove("B7", "B8");
	cb.submitMove("D3", "H7");
	cout << '\n';

	cb.submitMove("B8", "C8");
	cb.submitMove("F7", "G6");
	cout << '\n';

	cb.submitMove("C8", "E6");
	cout << '\n';

	cout << "==========================\n";
	cout << "Test for moving into check\n";
	cout << "==========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("D2", "D4");
	cb.submitMove("E7", "E5");
	cout << '\n';

	cb.submitMove("G1", "F3");

	cb.submitMove("D8", "G5");
	cout << '\n';

	cb.submitMove("E1", "D2");
	cout << '\n';

	cout << "===========================\n";
	cout << "Test for king side castling\n";
	cout << "===========================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("F1", "B5");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("G1", "F3");
	cb.submitMove("E7", "E5");
	cout << '\n';

	cb.submitMove("E1", "G1");
	cout << '\n';

	cout << "====================================\n";
	cout << "Test for illegal queen side castling\n";
	cout << "====================================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("D1", "F3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D2", "D3");
	cb.submitMove("D5", "D4");
	cout << '\n';

	cb.submitMove("C1", "E3");
	cb.submitMove("D4", "E3");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("E3", "F2");
	cout << '\n';

	cb.submitMove("E1", "C1"); // illegal move
	cb.submitMove("F3", "F2");
	cb.submitMove("G8", "F6");
	cout << '\n';

	cb.submitMove("E1", "C1"); // still illegal
	cout << '\n';

	cout << "========================================\n";
	cout << "2nd Test for illegal queen side castling\n";
	cout << "======================================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("D1", "F3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D2", "D3");
	cb.submitMove("E7", "E6");
	cout << '\n';

	cb.submitMove("C1", "G5");
	cb.submitMove("D8", "G5");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("D5", "E4");
	cout << '\n';

	cb.submitMove("E1", "C1");
	cout << '\n';

	cout << "=======================\n";
	cout << "Test for pawn promotion\n";
	cout << "=======================\n\n";

	cb.resetBoard();
	cout << '\n';

	cb.submitMove("E2", "E4");
	cb.submitMove("D7", "D5");
	cout << '\n';

	cb.submitMove("D1", "F3");
	cb.submitMove("B8", "D7");
	cout << '\n';

	cb.submitMove("D2", "D3");
	cb.submitMove("D5", "D4");
	cout << '\n';

	cb.submitMove("C1", "E3");
	cb.submitMove("D4", "E3");
	cout << '\n';

	cb.submitMove("B1", "C3");
	cb.submitMove("E3", "F2");
	cout << '\n';

	cb.submitMove("E1", "D1"); 
	cb.submitMove("G8", "H6");
	cout << '\n';

	cb.submitMove("F1", "E2"); // pawn is promoted to a queen as it has reached the furthest rank from its starting position.
	cb.submitMove("F2", "G1");
	cout << '\n';

	return 0;
}
