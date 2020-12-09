# pragma once
#include "Piece.hpp"
#include "Pawn.hpp"

Pawn::Pawn(Colour colour) : Piece(colour) {
    type = pawn;
}