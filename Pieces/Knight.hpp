#pragma once

class Knight : public Piece {

    private:

        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool onLShape(const char* start_pos, const char* end_pos) const;
        
    public:

    Knight(Colour colour);
    //move 
};