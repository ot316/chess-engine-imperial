#include "Piece.hpp"
#include "Pawn.hpp"

Pawn::Pawn(Colour colour) : Piece(colour) {
    type = pawn;
}

int Pawn::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onVerticalAdjacent(start_position, end_position))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_position, end_position, board))
        return NO_LINE_OF_SIGHT;
    
    return NO_ERROR;
}

bool Pawn::onVerticalAdjacent(const char* start_position, const char* end_position) const {
    // check moves
    return true;    
}