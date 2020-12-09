# pragma once
#include "Piece.hpp"
#include "Knight.hpp"

Knight::Knight(Colour colour) : Piece(colour) {
    type = knight;
}