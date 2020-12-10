#pragma once

class King : public Piece {

    private:

        int validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

    King(Colour colour);
    //move 
};