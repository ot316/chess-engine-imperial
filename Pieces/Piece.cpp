#include "Piece.hpp"

Piece::Piece(Colour colour) : colour(colour) {}

const Colour Piece::getColour() const {
    return colour;
}

const Type Piece::getType() const {
    return type;
}

int Piece::isValidMove(const char* starting_position, const char* end_position, Piece* board[][8], Colour player_turn) const {

    // Check turn matches piece
    if (player_turn != this->colour)
        return WRONG_TURN;
    
    // Check if the end position is occupied by a friendly piece
    const auto file = end_position[0] - 'A';
    const auto rank = end_position[1] - '1';
    if (board[file][rank] != nullptr) {
        if (board[file][rank]->getColour() == this->colour)
            return OCCUPIED_SQUARE;
    }

    /* Check the piece can move to the end position given its individual rules of movement,
    and check that there are no pieces obstructing the movement */
    int error_code = this->validPieceMovement(starting_position, end_position, board);
    if (error_code)
        return error_code;

    return true;
}

// Shared movement primitive validator functions
bool Piece::onDiagonal(const char* starting_position, const char* end_position) const {

}

bool Piece::onLine(const char* starting_position, const char* end_position) const {

}

bool Piece::ajdacent(const char* starting_position, const char* end_position) const {

}