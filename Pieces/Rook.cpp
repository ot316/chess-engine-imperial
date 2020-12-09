# pragma once
#include "Piece.hpp"
#include "Rook.hpp"

Rook::Rook(Colour colour) : Piece(colour) {
    type = rook;
}