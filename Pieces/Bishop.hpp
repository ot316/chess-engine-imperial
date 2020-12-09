#pragma once

class Bishop : public Piece {

    private:

        int validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const;
        
    public:

    Bishop(Colour colour);
    //move 
};