#include "Piece.hpp"
#include "Queen.hpp"

Queen::Queen(Colour colour) : Piece(colour) {
    type = queen;
}

int Queen::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onDiagonal(start_pos, end_pos) && !onLine(start_pos, end_pos))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;

    return NO_ERROR;
}