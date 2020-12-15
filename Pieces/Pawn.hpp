#pragma once

class Pawn : public Piece {
    
    private:

        // Used to keep track of movement to prevent a pawn from moving 2 squares forward when it has moved previously.
        bool has_moved = false;
        
        // Check if a knight can legally move between the given positions.
        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Helper function for legalPieceMovement.
        bool onVerticalAdjacent(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Check the pawn has line of sight between the given positions.
        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

        Pawn(Colour colour);

        // One way setter function for has_moved.
        void moved();

        // Getter function for has_moved.
        bool hasMoved() const;
};