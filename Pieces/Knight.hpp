#pragma once

class Knight : public Piece {

    private:

        bool validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const;

        bool onLShape(const char* start_position, const char* end_position, Piece* board[][8]) const;
        
    public:

    Knight(Colour colour);
    //move 
};