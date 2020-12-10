#pragma once

class Bishop : public Piece {

    private:

        int validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool validLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;
        
    public:

    Bishop(Colour colour);
    //move 
};