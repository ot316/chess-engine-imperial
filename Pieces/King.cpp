#include "Piece.hpp"
#include "King.hpp"

King::King(Colour colour) : Piece(colour) {
    this->type = king;
}


int King::legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!ajdacentTo(start_pos, end_pos))
        return INVALID_MOVEMENT;
        
    return NO_ERROR;
}


bool King::hasMoved() const {
    return has_moved;
}


void King::moved() {
    this->has_moved = true;
}