#include "Piece.hpp"
#include "Queen.hpp"

Queen::Queen(Colour colour) : Piece(colour) {
    type = queen;
}