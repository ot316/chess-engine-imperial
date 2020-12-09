#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(Colour colour) : Piece(colour) {
    type = rook;
}

int Rook::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onLine(start_position, end_position))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_position, end_position, board))
        return NO_LINE_OF_SIGHT;

    return NO_ERROR;
}