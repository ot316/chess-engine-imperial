#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(Colour colour) : Piece(colour) {
    type = rook;
}

bool Rook::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onLine(start_position, end_position, board))
        return false;
    
    if (!validLineOfSight(start_position, end_position, board))
        return false;
}