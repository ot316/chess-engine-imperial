#include "Piece.hpp"
#include "Knight.hpp"

Knight::Knight(Colour colour) : Piece(colour) {
    type = knight;
}

int Knight::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onLShape(start_pos, end_pos))
        return INVALID_MOVEMENT;

    return NO_ERROR;
}

bool Knight::onLShape(const char* start_pos, const char* end_pos) const {
    return false;    
}