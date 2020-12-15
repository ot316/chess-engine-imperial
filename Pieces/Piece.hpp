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

        int moved_count = 0;

        Colour colour;

        Type type = null;

        // Function is overwritten by each piece according to the pieces individual rules.
        virtual int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {return NO_ERROR;};

        // Checks if there is a piece obstructing the path from the start position ot the end position.
        virtual bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const {return NO_ERROR;}; 

        // These functions define which motion primitives apply to the given pair of coordinates.
        bool onDiagonal(const char* start_pos, const char* end_pos) const;

        bool onLine(const char* start_pos, const char* end_pos) const;

        bool ajdacentTo(const char* start_pos, const char* end_pos) const;

    public:

        Piece(Colour colour);

        virtual ~Piece();

        /* Checks if the correct player's piece is being moved, that a friendly piece is not at the end position
        and that the movement is legal given the pieces individual rules */
        int isLegalMove(const char* start_pos, const char* end_pos, Piece* board[][8], Colour player_turn) const;

        // Virtual function to check if a pawn has completed its first move.
        virtual bool hasMoved() const {return 0;};

        virtual void moved() {return;};

        // Return the pieces colour
        const Colour getColour() const;

        // Return the pieces type.
        const Type getType() const;


};