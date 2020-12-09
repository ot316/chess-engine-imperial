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
    using std::cerr;

    if(!checkInput(start_position, end_position)) {
        return;
    }

    if(this->outcome != in_play) {
        cerr << "The current game has ended, please reset the board.\n";
        return;
    }

    const auto file = start_position[0] - 'A';
    const auto rank = start_position[1] - '1';

    int error_code = board[file][rank]->isValidMove(start_position, end_position, board, player_turn);
    if (error_code == WRONG_TURN) {
        cerr << "Cannot move piece, it's not " << show_colour[board[file][rank]->getColour()];
        cerr << "'s turn.\n";
        return;
    }
    if (error_code == OCCUPIED_SQUARE) {
        cerr << end_position << " is occupied by a friendly piece.\n";
        return;
    }
    if (error_code == INVALID_MOVEMENT) {
        cerr << show_colour[board[file][rank]->getColour()];
        cerr << "'s " << show_type[board[file][rank]->getType()];
        cerr <<" cannot move to " << end_position << ".\n";
        return;
    }
    if (error_code == NO_LINE_OF_SIGHT) {
        cerr << show_colour[board[file][rank]->getColour()];
        cerr << "'s " << show_type[board[file][rank]->getType()];
        cerr <<" cannot move to " << end_position << " as there is a piece in the way.\n";
        return;

    }
    // check if moving into check
    if (error_code == MOVING_INTO_CHECK) {
        return;

    }
    



}

void ChessBoard::configureBoard() {
    // Initilise board pointers to nullptr
    for (auto rank = 2u; rank < 6; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            board[file][rank] = nullptr;
        }
    }

    // Create pieces on heap
    Colour team_identifier = white;

    for (auto i = 0u; i < 8; i += 7) {

        board[0][i] = new Rook(team_identifier);
        board[1][i] = new Knight(team_identifier);
        board[2][i] = new Bishop(team_identifier);
        board[3][i] = new King(team_identifier);
        board[4][i] = new Queen(team_identifier);
        board[5][i] = new Bishop(team_identifier);
        board[6][i] = new Knight(team_identifier);
        board[7][i] = new Rook(team_identifier);

        for(auto file = 0u; file < 8; ++file) {
            int rank_offset = ((team_identifier == white) ? (i + 1) : (i - 1)); // toggle rank offset depending on colour
            board[file][rank_offset] = new Pawn(team_identifier);
        }

        team_identifier = black;
    }
    displayBoard();

}

bool ChessBoard::checkInput(const char* start_position, const char* end_position) {
    // Check Coordinates are within range
    using std::cerr;
    if (strlen(start_position) != 2 ||
            start_position[0] < 'A' ||
            start_position[0] > 'H' ||
            start_position[1] < '1' ||
            start_position[1] > '8') {
                cerr << start_position << "is in an invalid starting coordinate.\n";
                return false;
    }
    if (strlen(end_position) != 2 ||
            end_position[0] < 'A' ||
            end_position[0] > 'H' ||
            end_position[1] < '1' ||
            end_position[1] > '8') {
            cerr << end_position << "is in an invalid end coordinate.\n";
            return false;
    }
    const auto file = start_position[0] - 'A';
    const auto rank = start_position[1] - '1';
    if (board[file][rank] == nullptr) {
        cerr << "The starting position " << start_position << " does not contain a piece.\n";
        return false;
    }
    return true;
}


void ChessBoard::displayBoard() const {
    using namespace std;

    for (auto i = 0u; i < 185; i++)
        cout << "_";
    cout << "\n\n\n";

    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] == nullptr) 
                cout << "   Empty    \t|\t";
            else {
                Piece* piece = board[file][rank];
                cout << show_colour[piece->getColour()] << " ";
                cout << show_type[piece->getType()] << "\t|\t";
            }
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