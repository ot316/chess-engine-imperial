# pragma once
#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(Colour colour) : Piece(colour) {
    type = bishop;
}