#pragma once

class Bishop : public Piece {

    private:

        bool validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const;
        
    public:

    Bishop(Colour colour);
    //move 
};