#pragma once
#include<cstring>

enum Colour {white, black};
const char show_colours[][6] = {"White", "Black"};

enum Type {null, pawn, knight, bishop, rook, queen, king};
const char show_type[][7] = {"Error", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

class Piece {

    protected:
    Colour colour;
    Type type = null;

    public:

    Piece(Colour colour);

    const Colour getColour() const;

    const Type getType() const;

};