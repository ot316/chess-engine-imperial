#include "Piece.hpp"
#include "Bishop.hpp"

Bishop::Bishop(Colour colour) : Piece(colour) {
    this->type = bishop;
}


int Bishop::legalPieceMovement(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    if (!onDiagonal(start_pos, end_pos))
        return INVALID_MOVEMENT;
    
    if (!legalLineOfSight(start_pos, end_pos, board))
        return NO_LINE_OF_SIGHT;
    
    return NO_ERROR;
}


bool Bishop::legalLineOfSight(const char* start_pos, const char* end_pos, Piece* board[][8]) const {
    auto start_x = start_pos[0] - 'A';
    auto start_y = start_pos[1] - '1';
    auto end_x = end_pos[0] - 'A';
    auto end_y = end_pos[1] - '1';
    auto delta_x = end_x - start_x;
    auto delta_y = end_y - start_y;

    // inverse multiplier to iterate over squares in different directions depending on movement direction.
	auto multiplier = ((delta_x < 0 && delta_y < 0) || (delta_x > 0 && delta_y > 0) ? 1 : -1);
    
	if (delta_x < 0) 
		for (auto i = -1; i != delta_x; --i)
			if (board[start_x + i][start_y + (i * multiplier)] != nullptr)
				return false;

	if (delta_x > 0)
    	for (auto i = 1; i != delta_x; ++i)
			if (board[start_x + i][start_y + (i * multiplier)] != nullptr) 
				return false;
	return true; 
}