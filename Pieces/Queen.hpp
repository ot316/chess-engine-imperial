#pragma once

class Queen : public Piece {

    private:

        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;
        
    public:

        Queen(Colour colour);
    //move 
};