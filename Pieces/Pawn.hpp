#pragma once

class Pawn : public Piece {
    
    private:

        bool moved = 0;

        // Used to modify movement behaviour depending on whether the pawn has moved previously.
        //mutable unsigned int move = 0;

        int legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        // Helper function to check if a move is legal for a pawn.
        bool onVerticalAdjacent(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

        bool legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const;

    public:

        Pawn(Colour colour);

        void hasMoved(); 
};