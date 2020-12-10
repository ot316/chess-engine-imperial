#pragma once

class Queen : public Piece {
    
    private:

        int validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const ;
        
    public:

    Queen(Colour colour);
    //move 
};