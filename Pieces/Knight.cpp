#include "Piece.hpp"
#include "Knight.hpp"

Knight::Knight(Colour colour) : Piece(colour) {
    type = knight;
}

int Knight::validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {
    if (!onLShape(start_position, end_position))
        return false;
}

bool Knight::onLShape(const char* start_position, const char* end_position) const {

}