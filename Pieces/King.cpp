#include "Piece.hpp"
#include "King.hpp"

King::King(Colour colour) : Piece(colour) {
    type = king;
}

int King::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!ajdacent(start_position, end_position))
        return INVALID_MOVEMENT;
        
    return NO_ERROR;
}