#include "Piece.hpp"

Piece::Piece(Colour colour) : colour(colour) {}

Piece::~Piece(){}

const Colour Piece::getColour() const {
    return colour;
}

const Type Piece::getType() const {
    return type;
}

int Piece::isValidMove(const char* start_pos, const char* end_pos, Piece* board[][8], Colour player_turn) const {

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
    and check that there are no pieces obstructing the movement, should the piece require this. */
    int error_code = this->validPieceMovement(start_pos, end_pos, board);
    if (error_code)
        return error_code;

    return NO_ERROR;
}


// Shared movement primitive validator functions
bool Piece::onDiagonal(const char* start_pos, const char* end_pos) const {
    auto delta_x = abs(start_pos[0] - 'A') - (end_pos[0] - 'A');
    auto delta_y = abs(start_pos[1] - '1') - (end_pos[1] - '1');

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
    auto delta_x = abs(start_pos[0] - 'A') - (end_pos[0] - 'A');
    auto delta_y = abs(start_pos[1] - '1') - (end_pos[1] - '1');

    if ((delta_x + delta_y != 0) && (delta_x + delta_y <= 2))
        return true;
    return false;
}