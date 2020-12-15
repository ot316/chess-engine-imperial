#pragma once

class Knight : public Piece {

    private:

        // Check if a knight can legally move between the given positions.
        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Helper function for legalPieceMovement.
        bool onLShape(const char* start_pos, const char* end_pos) const;
        
    public:

        Knight(Colour colour);
};