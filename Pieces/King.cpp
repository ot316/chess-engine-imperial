#include "Piece.hpp"
#include "King.hpp"

King::King(Colour colour) : Piece(colour) {
    type = king;
}