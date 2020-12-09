#pragma once

class Rook : public Piece {

    private:

        bool validPieceMovement(const char* sart_position, const char* end_position, Piece* board[][8]) const;
        
    public:

    Rook(Colour colour);
    //move 
};