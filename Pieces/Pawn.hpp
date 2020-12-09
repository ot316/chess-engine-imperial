#pragma once

class Pawn : public Piece {
    
    private:

        int moves = 0;

        int validPieceMovement(const char* start_position, const char* end_position, Piece* board[][8]) const;

        bool onVerticalAdjacent(const char* start_position, const char* end_position) const;

    public:

    Pawn(Colour colour);
    //move 
};