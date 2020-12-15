#include "Piece.hpp"
#include <iostream>

Piece::Piece(Colour colour) : colour(colour) {}


Piece::~Piece(){}


const Colour Piece::getColour() const {
    return colour;
}


const Type Piece::getType() const {
    return type;
}


int Piece::isLegalMove(const char* start_pos, const char* end_pos, Piece* board[][8], Colour player_turn) const {
    if (start_pos == end_pos)
        return SAME_START_AND_END_SQUARE;
        
    // Check turn matches piece
    if (player_turn != this->colour)
        return WRONG_TURN;
    
    // Check if the end position is occupied by a friendly piece
    const auto file = end_pos[0] - 'A';
    const auto rank = end_pos[1] - '1';
    if (board[file][rank] != nullptr) {
        if (board[file][rank]->getColour() == this->colour)
            return OCCUPIED_SQUARE;
    }

    /* Check the piece can move to the end position given its individual rules of movement,
    and check that there are no pieces obstructing the movement, should the piece require this. 
    e.g. knights and kings do not need to check line of sight. */
    int error_code = this->legalPieceMovement(start_pos, end_pos, board);
    if (error_code)
        return error_code;

    return NO_ERROR;
}


// All below functions are shared movement validator functions.
bool Piece::onDiagonal(const char* start_pos, const char* end_pos) const {
    auto delta_x = abs(end_pos[0] - start_pos[0]);
    auto delta_y = abs(end_pos[1] - start_pos[1]);

    if (delta_x == delta_y) {
        if (delta_x)
            return true;
    }
    return false;
}


bool Piece::onLine(const char* start_pos, const char* end_pos) const {
    if (start_pos != end_pos) {
        if ((start_pos[0] == end_pos[0] || start_pos[1] == end_pos[1]))
                return true;
    }
    return false;
}


bool Piece::ajdacentTo(const char* start_pos, const char* end_pos) const {
    using namespace std;
    auto delta_x = abs(end_pos[0] - start_pos[0]);
    auto delta_y = abs(end_pos[1] - start_pos[1]);

    if (delta_x == 1 || delta_y == 1)
        if (delta_x + delta_y <= 2)
            return true;

    return false;
}