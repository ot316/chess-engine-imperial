#pragma once

class Rook : public Piece {

    private:

        int validPieceMovement(const char* sart_position, const char* end_pos, Piece* board[][8]) const;
        
    public:

    Rook(Colour colour);
    //move 
};