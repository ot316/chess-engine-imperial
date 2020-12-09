#pragma once

class Queen : public Piece {
    private:

        bool validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const ;
        
    public:

    Queen(Colour colour);
    //move 
};