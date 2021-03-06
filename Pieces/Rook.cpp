#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(Colour colour) : Piece(colour) {
    this->type = rook;
}


int Rook::legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onLine(start_pos, end_pos))
        return INVALID_MOVEMENT;
    
    if (!legalLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;

    return NO_ERROR;
}


bool Rook::legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    auto start_x = start_pos[0] - 'A';
    auto start_y = start_pos[1] - '1';
    auto end_x = end_pos[0] - 'A';
    auto end_y = end_pos[1] - '1';
    auto delta_x = end_x - start_x;
    auto delta_y = end_y - start_y;

    // Change between increment and decrement depending on the direction of movement.
    auto increment = ((end_x > start_x || end_y > start_y) ? 1 : -1);

    if (!delta_x) {
        for (auto i = start_y + increment; i != end_y; i+=increment)
            if (board[start_x][i] != nullptr)
                return false;
    }

    if (!delta_y) {
        for (auto i = start_x + increment; i != end_x; i+=increment)
            if (board[i][start_y] != nullptr)
                return false;
    }

    return true;
}


bool Rook::hasMoved() const {
    return has_moved;
}


void Rook::moved() {
    this->has_moved = true;
}
