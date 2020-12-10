#include "Piece.hpp"
#include "King.hpp"

King::King(Colour colour) : Piece(colour) {
    type = king;
}

int King::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!ajdacentTo(start_pos, end_pos))
        return INVALID_MOVEMENT;
        
    return NO_ERROR;
}