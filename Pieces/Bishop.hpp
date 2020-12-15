#pragma once

class Bishop : public Piece {

    private:

        // Check the bishop can legally move between the given positions.
        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Check the bishop has line of sight between the given positions.
        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;
        
    public:

        Bishop(Colour colour);
};