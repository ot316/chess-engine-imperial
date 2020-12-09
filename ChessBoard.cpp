#include "ChessBoard.h"

ChessBoard::ChessBoard() {
    configureBoard();
}

ChessBoard::~ChessBoard() {
    clearBoard();
}

void ChessBoard::resetBoard() {
    clearBoard();
    configureBoard();
}

void ChessBoard::submitMove(const char* start_position, const char* end_position) {
    if(!checkInput(start_position, end_position)) {
        return;
    }

}

void ChessBoard::configureBoard() {
    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            board[file][rank] = nullptr;
        }
    }

    Colour team_identifier = white;

    for (auto i = 0u; i < 8; i = i + 7) {

        board[0][i] = new Rook(team_identifier);
        board[1][i] = new Knight(team_identifier);
        board[2][i] = new Bishop(team_identifier);
        board[3][i] = new King(team_identifier);
        board[4][i] = new Queen(team_identifier);
        board[5][i] = new Bishop(team_identifier);
        board[6][i] = new Knight(team_identifier);
        board[7][i] = new Rook(team_identifier);

        for(auto file = 0u; file < 8; ++file) {
            int index = ((team_identifier == white) ? (i + 1) : (i - 1)); // toggle rank offset depending on colour
            board[file][index] = new Pawn(team_identifier);
        }

        team_identifier = black;
    }
    displayBoard();

}

bool ChessBoard::checkInput(const char* start_position, const char* end_position) {
    using std::cerr;
    if (start_position[0] < 'A' ||
        start_position[0] > 'H' ||
        start_position[1] < '1' ||
        start_position[1] > '8' ||
        strlen(start_position) != 2)
        {
            cerr << start_position << "is in an invalid starting coordinate\n";
            return false;
        }
    return true;
}

void ChessBoard::displayBoard() {
    using namespace std;

    for (auto i = 0u; i < 185; i++)
        cout << "_";
    cout << "\n\n\n";

    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] != nullptr) {
                Piece* piece = board[file][rank];
                cout << show_colours[piece->getColour()] << " " << show_type[piece->getType()] << "\t|\t";
            }
            else
                cout << "   Empty    \t|\t";
        }
        cout << "\n\n";
        for (auto i = 0u; i < 185; i++)
            cout << "_";
        cout << "\n\n\n";
    }
}

void ChessBoard::clearBoard() {
    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] != nullptr)
                delete board[file][rank];
        }
    }
}