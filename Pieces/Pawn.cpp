#include "Piece.hpp"
#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(Colour colour) : Piece(colour) {
    type = pawn;
}

int Pawn::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onVerticalAdjacent(start_pos, end_pos, board))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;

    return NO_ERROR;
}

bool Pawn::onVerticalAdjacent(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    auto start_x = start_pos[0] - 'A';
    auto start_y = start_pos[1] - '1';
    auto end_x = end_pos[0] - 'A';
    auto end_y = end_pos[1] - '1';
    auto delta_y = end_y - start_y;
    auto delta_x = abs(end_x - start_x);

    // Reverse permitted direction depending on colour.
    if (this->getColour() == black)
        delta_y = delta_y * -1;

    // Allow 1 square diagonal movement if the square is occupied by an enemy piece.
    if (delta_x == 1 && delta_y == 1) 
        if (board[end_x][end_y] != nullptr)
            return true;

     if (delta_x == 0 && board[end_x][end_y] == nullptr) {
        // Allow the pawn to move 2 squares forwards only if it is on its first move.
        if (moved == 0) {
            if ((delta_y == 1) || (delta_y == 2)) 
                return true;      
        }
        // Allow single square forwards movement otherwise.
        else {
            if (delta_y == 1)
                return true;
        }
    }
    return false;    
}

bool Pawn::validLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    auto start_x = start_pos[0] - 'A';
    auto start_y = start_pos[1] - '1';
    auto end_x = end_pos[0] - 'A';
    auto end_y = end_pos[1] - '1';
    auto delta_x = end_y - start_y;

    if (!delta_x) {
        if(board[end_x][end_y] != 0)
                    return false;

        auto iterator = ((end_y > start_y) ? 1 : -1);

        for (int i = start_y + iterator; i != end_y; i = i + iterator)
        {
            if (board[start_x][i] != 0)
                return false;	
        }
	}
	return true;
}

void Pawn::hasMoved() {
    moved = true;
}