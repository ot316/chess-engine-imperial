#pragma once

class King : public Piece {

    private:

        // Keep track of movement for castling.
        bool has_moved = false;

        // Check the king can legally move between the given positions.
        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

        King(Colour colour);

        // One way setter function for has_moved.
        void moved();

        // Getter function for has_moved.
        bool hasMoved() const;
};