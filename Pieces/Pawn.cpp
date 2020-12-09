#include "Piece.hpp"
#include "Pawn.hpp"

Pawn::Pawn(Colour colour) : Piece(colour) {
    type = pawn;
}

bool Pawn::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onVerticalAdjacent(start_position, end_position, board))
        return false;
    
    if (!validLineOfSight(start_position, end_position, board))
        return false;
}

bool Pawn::onVerticalAdjacent(const char* start_position, const char* end_position, Piece* board[][8]) const {

}