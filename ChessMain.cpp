#include "ChessBoard.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb;
	// cout << '\n';

	// cb.submitMove("D7", "D6");
	// cout << '\n';

	// cb.submitMove("D4", "H6");
	// cout << '\n';

	// cb.submitMove("D2", "D4");
	// cout << '\n';

	// cb.submitMove("E7", "E5");
	// cout << '\n';

	// cb.submitMove("D4", "E5");
	// cout << '\n';

	// cb.submitMove("A7", "A5");
	// cout << '\n';

	// cb.submitMove("E5", "E6");
	// cout << '\n';

	// cb.submitMove("A5", "A4");
	// cout << '\n';	

	// cb.submitMove("G2", "G3");
	// cout << '\n';

	// cb.submitMove("A4", "A3");
	// cout << '\n';	

	// cb.submitMove("C1", "H6");
	// cout << '\n';

	// cb.submitMove("G7", "G6");
	// cout << '\n';

	// cb.submitMove("F1", "H3");
	// cout << '\n';

	// cb.submitMove("A8", "A6");
	// cout << '\n';

	// cb.submitMove("B2", "A3");
	// cout << '\n';

	// cb.submitMove("A6", "E6");
	// cout << '\n';

	// cb.submitMove("H3", "F5");
	// cout << '\n';

	// cb.submitMove("E6", "D6");
	// cout << '\n';

	// cb.submitMove("F5", "D3");
	// cout << '\n';

	// cb.submitMove("B7", "B5");
	// cout << '\n';

	// cb.submitMove("E1", "B4");
	// cout << '\n';

	// cb.submitMove("D6", "D3");
	// cout << '\n';

	// cb.submitMove("C2", "D3");
	// cout << '\n';

	// cb.submitMove("B8", "A6");
	// cout << '\n';

	// cb.submitMove("G1", "H3");
	// cout << '\n';

	// cb.submitMove("A6", "B4");
	// cout << '\n';
	//return 0;

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

	return 0;
}
