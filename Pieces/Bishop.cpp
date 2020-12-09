#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(Colour colour) : Piece(colour) {
    type = bishop;
}

bool Bishop::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onDiagonal(start_position, end_position, board))
        return false;
    
    if (!validLineOfSight(start_position, end_position, board))
        return false;
}