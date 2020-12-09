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

        bool isValidMove(const char* starting_position, const char* end_position, Piece* board[][8], Colour player_turn) const;

        virtual bool validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {return 0;};

        virtual bool validLineOfSight(const char* start_position, const char* end_position, Piece* board[][8]) const {return 0;};

        bool onDiagonal(const char* start_position, const char* end_position, Piece* board[][8]) const;

        bool onLine(const char* start_position, const char* end_position, Piece* board[][8]) const;

        bool ajdacent(const char* start_position, const char* end_position, Piece* board[][8]) const;

    public:

        Piece(Colour colour);

        const Colour getColour() const;

        const Type getType() const;

};