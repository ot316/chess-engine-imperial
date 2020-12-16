#pragma once
#include "../errors.hpp"
#include <cstring>
#include <cmath>

// Used to improve readability and to print types and colours to the terminal.
enum Colour {white, black};
const char print_colour[][6] = {"White", "Black"};

enum Type {null, pawn, knight, bishop, rook, queen, king};
const char print_type[][7] = {"Error", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};
const char print_unicode_symbol_black[][7] = {"  ", "♙", "♘", "♗", "♖", "♕", "♔"};
const char print_unicode_symbol_white[][7] = {"  ", "♟︎", "♞", "♝", "♜", "♛", "♚"};

class Piece {

    protected:

        Colour colour;

        Type type = null;

        // Function is overwritten by each piece according to the pieces individual rules.
        virtual int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {return NO_ERROR;};

        // Checks if there is a piece obstructing the path from the start position ot the end position.
        virtual bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const {return NO_ERROR;}; 

        // These functions validate which motion primitives apply to the given positions.
        bool onDiagonal(const char* start_pos, const char* end_pos) const;

        bool onLine(const char* start_pos, const char* end_pos) const;

        bool ajdacentTo(const char* start_pos, const char* end_pos) const;

    public:

        Piece(Colour colour);

        virtual ~Piece();

        /* Checks if the correct player's piece is being moved, that a friendly piece is not at the end position
        and that the movement is legal given the pieces individual rules */
        int isLegalMove(const char* start_pos, const char* end_pos, Piece* board[][8], Colour player_turn) const;

        // Virtual getter function to check if a piece has moved previously. Returns 0 on pieces where this function is not required.
        virtual bool hasMoved() const {return 0;};

        // Virtual function to determine if a piece has moved.
        virtual void moved() {return;};

        // Getter function to return the pieces colour
        const Colour getColour() const;

        // Getter function to return the pieces type.
        const Type getType() const;


};