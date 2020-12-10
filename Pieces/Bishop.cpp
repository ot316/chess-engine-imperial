#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(Colour colour) : Piece(colour) {
    type = bishop;
}

int Bishop::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onDiagonal(start_pos, end_pos))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;
    
    return NO_ERROR;
}