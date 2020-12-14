#pragma once

class Pawn : public Piece {
    
    private:

        int moved_count = 0;

        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Helper function to check if a move is legal for a pawn.
        bool onVerticalAdjacent(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

        Pawn(Colour colour);

        void moved();

        int hasMoved() const;
};