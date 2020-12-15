#include "Piece.hpp"
#include "Knight.hpp"

Knight::Knight(Colour colour) : Piece(colour) {
    type = knight;
}


int Knight::legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onLShape(start_pos, end_pos))
        return INVALID_MOVEMENT;

    return NO_ERROR;
}


bool Knight::onLShape(const char* start_pos, const char* end_pos) const {
    const auto delta_x = abs(end_pos[0] - start_pos[0]);
    const auto delta_y = abs(end_pos[1] - start_pos[1]);

    if (delta_x + delta_y == 3)
        if (delta_x != 0 && delta_y != 0)
            return true;
    return false;    
}