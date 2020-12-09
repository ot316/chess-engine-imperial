#pragma once
#include "Pieces/Piece.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/Rook.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/King.hpp"
#include <iostream>

enum Outcome {in_play, white_wins, black_wins, stalemate};

class ChessBoard {

    private:

        bool game_over;

        Colour player_turn = white;

        Outcome outcome;
        
        Piece* board[8][8];

        // Sets up the chess board ready for a new game.
        void configureBoard();

        // Helper function to check the start and end coordinates are valid.
        bool checkInput(const char* start_position, const char* end_position);

        // Helper function to ensure a move does not place the king in check.
        int movingIntoCheck(const char* start_position, const char* end_position) const;

        void toggle(Colour& player_turn);

        Outcome checkGameOutcome();

        void clearBoard();

    public:
    
        ChessBoard();

        ~ChessBoard();

        // Moves a piece from the start position to the end position.
        void submitMove(const char* start_position, const char* end_position);

        // Discards the current game and resets the board.
        void resetBoard();
        
        // Displays an Ascii chessboard representing the games current state.
        void displayBoard() const;

};