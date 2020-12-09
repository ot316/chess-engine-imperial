#include "Piece.hpp"
#include "Queen.hpp"

Queen::Queen(Colour colour) : Piece(colour) {
    type = queen;
}

int Queen::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onDiagonal(start_position, end_position) && !onLine(start_position, end_position))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_position, end_position, board))
        return NO_LINE_OF_SIGHT;

    return NO_ERROR;
}