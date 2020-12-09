#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(Colour colour) : Piece(colour) {
    type = bishop;
}

int Bishop::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onDiagonal(start_position, end_position))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_position, end_position, board))
        return NO_LINE_OF_SIGHT;
    
    return NO_ERROR;
}