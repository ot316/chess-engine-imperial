#pragma once

class Queen : public Piece {

    private:

        // Check if a queen can legally move between the given positions.
        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Check the queen has line of sight between the given positions.
        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;
        
    public:

        Queen(Colour colour);
};