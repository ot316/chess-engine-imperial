#pragma once

class King : public Piece {

    private:

        bool has_moved = false;

        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

        King(Colour colour);

        void moved();

        bool hasMoved() const;
};