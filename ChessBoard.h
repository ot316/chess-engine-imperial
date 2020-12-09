#pragma once
#include "Pieces/Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/Rook.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/King.hpp"

enum Result {white_wins, black_wins, stalemate};

class ChessBoard {

    private:

    bool game_over;

    Colour player_turn;

    Result result;
    
    Piece* board[8][8];

    void configureBoard();

    bool checkInput(const char* start_position, const char* end_position);

    void clearBoard();

    public:
    
    ChessBoard();

    ~ChessBoard();

    void submitMove(const char* start_position, const char* end_position);

    void resetBoard();

};