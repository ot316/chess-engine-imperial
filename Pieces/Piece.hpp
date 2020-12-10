#pragma once
#include "../errors.hpp"
#include <cstring>
#include <cmath>

enum Colour {white, black};
const char print_colour[][6] = {"White", "Black"};

enum Type {null, pawn, knight, bishop, rook, queen, king};
const char print_type[][7] = {"Error", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};

class Piece {

    protected:

        Colour colour;

        Type type = null;

        virtual int validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {return NO_ERROR;};

        bool validLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool onDiagonal(const char* start_pos, const char* end_pos) const;

        bool onLine(const char* start_pos, const char* end_pos) const;

        bool ajdacentTo(const char* start_pos, const char* end_pos) const;

    public:

        Piece(Colour colour);

        virtual ~Piece();

        int isValidMove(const char* start_pos, const char* end_pos, Piece* board[][8], Colour player_turn) const;

        virtual void retractMove() const {return;};

        const Colour getColour() const;

        const Type getType() const;

};