#include "Piece.hpp"
#include "Pawn.hpp"

Pawn::Pawn(Colour colour) : Piece(colour) {
    type = pawn;
}

int Pawn::validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onVerticalAdjacent(start_pos, end_pos))
        return INVALID_MOVEMENT;
    
    if (!validLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;

    move++;
    return NO_ERROR;
}

bool Pawn::onVerticalAdjacent(const char* start_pos, const char* end_pos) const {
    if (start_pos[0] != end_pos[0])
        return false;

    auto delta_y = abs((start_pos[1] - '1') - (end_pos[1] - '1'));

    if (move == 0) {
        if ((delta_y == 1) || (delta_y == 2)) 
            return true;      
    }
    else {
        if (delta_y == 1)
            return true;
    }

    return false;    
}

void Pawn::retractMove() const {
    move--;
}