#pragma once

class Pawn : public Piece {
    
    private:

        mutable unsigned int move = 0;

        int validPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool onVerticalAdjacent(const char* start_pos, const char* end_pos) const;

    public:

    Pawn(Colour colour);

    void retractMove() const; 
};