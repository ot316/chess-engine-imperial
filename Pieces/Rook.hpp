#pragma once

class Rook : public Piece {

    private:

        // Keep track of movement for castling.
        bool has_moved = false;

        // Check the rook can legally move between the given positions.
        int legalPieceMovement(const char* sart_position, const char* end_pos, Piece* board[][8]) const;

        // Check the rook has line of sight between the given positions.
        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;
        
    public:

        Rook(Colour colour);

        // One way setter function for has_moved.
        void moved();

        // Getter function for has_moved.
        bool hasMoved() const;
};