#include "Piece.hpp"
#include "Queen.hpp"

Queen::Queen(Colour colour) : Piece(colour) {
    type = queen;
}

bool Queen::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onDiagonal(start_position, end_position, board))
        return false;
    
    if (!onLine(start_position, end_position, board))
        return false;

    if (!validLineOfSight(start_position, end_position, board))
        return false;

}