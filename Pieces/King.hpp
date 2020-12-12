#pragma once

class King : public Piece {

    private:

        bool moved = 0;

        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

    King(Colour colour);
    
    void hasMoved(); 
};