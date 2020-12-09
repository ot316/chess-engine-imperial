#pragma once

enum Colour {white, black};

enum Type {null, pawn, knight, bishop, rook, queen, king};

class Piece {

    protected:
    Colour colour;
    Type type = null;

    public:

    Piece(Colour colour);

    const Colour getColour() const;

    const Type getType() const;

};