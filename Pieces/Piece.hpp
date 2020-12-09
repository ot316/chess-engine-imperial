#pragma once
#include "../errors.hpp"
#include <cstring>

enum Colour {white, black};
const char show_colour[][6] = {"White", "Black"};

enum Type {null, pawn, knight, bishop, rook, queen, king};
const char show_type[][7] = {"Error", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

class Piece {

    protected:

        Colour colour;

        Type type = null;

        virtual int validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const {return 0;};

        virtual bool validLineOfSight(const char* start_position, const char* end_position, Piece* board[][8]) const {return 0;};

        bool onDiagonal(const char* start_position, const char* end_position) const;

        bool onLine(const char* start_position, const char* end_position) const;

        bool ajdacent(const char* start_position, const char* end_position) const;

    public:

        Piece(Colour colour);

        int isValidMove(const char* starting_position, const char* end_position, Piece* board[][8], Colour player_turn) const;

        const Colour getColour() const;

        const Type getType() const;

};