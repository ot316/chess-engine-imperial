#pragma once

class Knight : public Piece {

    private:

        int validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const;

        bool onLShape(const char* start_position, const char* end_position) const;
        
    public:

    Knight(Colour colour);
    //move 
};