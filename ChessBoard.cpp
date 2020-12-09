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
    bool error = checkInput(start_position, end_position);
}

void ChessBoard::configureBoard() {
    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            board[file][rank] == nullptr;
        }
    }

    for (auto i = 0u; i < 8; i = i + 7) {

        Colour team_identifier = white;

        board[i][0] = new Rook(team_identifier);
        board[i][1] = new Knight(team_identifier);
        board[i][2] = new Bishop(team_identifier);
        board[i][3] = new King(team_identifier);
        board[i][4] = new Queen(team_identifier);
        board[i][5] = new Bishop(team_identifier);
        board[i][6] = new Knight(team_identifier);
        board[i][7] = new Rook(team_identifier);

        for(auto file = 0u; file < 8; ++file) {
            int index = (team_identifier == white ? (i + 1) : (i - 1));
            board[index][file] = new Pawn(team_identifier);
        }

        team_identifier = black;
    }

}

bool ChessBoard::checkInput(const char* start_position, const char* end_position) {
    // check inputs
    return true;
}

void ChessBoard::clearBoard() {
    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] != nullptr)
                delete board[file][rank];
        }
    }
}