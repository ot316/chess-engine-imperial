#include "Piece.hpp"

Piece::Piece(Colour colour) : colour(colour) {}

const Colour Piece::getColour() const {
    return colour;
}

const Type Piece::getType() const {
    return type;
}