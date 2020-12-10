#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(Colour colour) : Piece(colour) {
    type = rook;
}

int Rook::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onLine(start_pos, end_pos))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;

    return NO_ERROR;
}