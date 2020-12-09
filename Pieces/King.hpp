#pragma once

class King : public Piece {

    private:

        int validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const;

    public:

    King(Colour colour);
    //move 
};