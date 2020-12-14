#pragma once

class Rook : public Piece {

    private:

        int moved_count = 0;

        int legalPieceMovement(const char* sart_position, const char* end_pos, Piece* board[][8]) const;

        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;
        
    public:

        Rook(Colour colour);

        void moved();

        int hasMoved() const;
};