#include "ChessBoard.h"
#include <unistd.h>
#include <algorithm>

// mapping for piece values
std::unordered_map<Type, int> piece_values({{pawn, 1}, {knight, 3}, {bishop, 3}, {rook, 5}, {queen, 9}});

ChessBoard::ChessBoard() {
    configureBoard();
}


ChessBoard::~ChessBoard() {
    clearBoard();
}


void ChessBoard::resetBoard() {
    clearBoard();
    configureBoard();
}


void ChessBoard::resign() {
    // Check which player resigns
    if (player_turn == white) {
        output_status = "White has resigned, Black wins.\n\n\t";
        outcome = black_wins; 
        return;
    }
        
    else {
        output_status = "Black has resigned, White wins.\n\n\t";
        outcome = white_wins;
        return;
    }
}

bool ChessBoard::inPlay() {
    return outcome ? false : true;
}


void ChessBoard::submitMove(const char* start_pos, const char* end_pos) {
    using std::cerr;
    using std::cout;

    output_status.clear();

    Colour other_player_turn = player_turn;
    toggle(other_player_turn);

    // check game is ongoing
    if(outcome != in_play) {
        output_status = "The current game has ended, please reset the board.\n\n\t";
        return;
    }

    // check input is valid
    if(!checkInput(start_pos, end_pos)) {
        return;
    }

    // Special case if King is castling
    if (castling(start_pos, end_pos))
        return;
    
    const auto file = start_pos[0] - 'A';
    const auto rank = start_pos[1] - '1';

    // Check if move is legal.
    int error_code = board[file][rank]->isLegalMove(start_pos, end_pos, board, player_turn);

    switch (error_code) {
        case WRONG_TURN :
            output_status += "Cannot move piece, it's not " + std::string(print_colour[board[file][rank]->getColour()]);
            output_status += "'s turn.\n\n";
            return;
        case SAME_START_AND_END_SQUARE :
            output_status += "The start square ";
            output_status += start_pos; 
            output_status += " is the same as the end square ";
            output_status += end_pos;
            output_status += ".\n\n";
            return;
        case OCCUPIED_SQUARE :
            output_status += end_pos;
            output_status += " is occupied by a friendly piece.\n\n\n";
            return;
        case INVALID_MOVEMENT :
            output_status += print_colour[board[file][rank]->getColour()];
            output_status += "'s " + std::string(print_type[board[file][rank]->getType()]);
            output_status += " cannot move from ";
            output_status += start_pos;
            output_status += " to ";
            output_status += end_pos;
            output_status += ".\n\n";
            return;
        case NO_LINE_OF_SIGHT :
            output_status += print_colour[board[file][rank]->getColour()];
            output_status += "'s " + std::string(print_type[board[file][rank]->getType()]);
            output_status += " cannot move from " ;
            output_status += start_pos;
            output_status += " to ";
            output_status += end_pos;
            output_status += " as there is a piece in the way.\n\n";
            return;
    }
    
    // Check if the move results in the mover's king being in check.
    if (movingIntoCheck(start_pos, end_pos) == MOVING_INTO_CHECK) {
        if (in_check[player_turn]) {
            output_status += "Moving ";
            output_status += print_colour[player_turn];
            output_status += "'s ";
            output_status += print_type[board[file][rank]->getType()];
            output_status += " from ";
            output_status += start_pos;
            output_status += " to ";
            output_status += end_pos;
            output_status += " is illegal because " + std::string(print_colour[player_turn]);
            output_status += " is in check.\n\n";

        }
        else {
            output_status += "Moving " + std::string(print_colour[board[file][rank]->getColour()]);
            output_status += "'s " + std::string(print_type[board[file][rank]->getType()]);
            output_status += " from ";
            output_status += start_pos;
            output_status += " to ";
            output_status += end_pos;
            output_status += " would expose ";
            output_status += print_colour[board[file][rank]->getColour()];
            output_status += "'s King to check.\n\n";
        }
        return;

    }
    // Move piece.
    const auto& start_x = file;
    const auto& start_y = rank;
    const auto end_x = end_pos[0] - 'A';
    const auto end_y = end_pos[1] - '1';

    output_status += print_colour[board[file][rank]->getColour()];
    output_status += "'s " + std::string(print_type[board[file][rank]->getType()]);
    output_status += " moves from ";
    output_status += start_pos;
    output_status += " to ";
    output_status += end_pos;

    board[start_x][start_y]->moved();    // Used to keep track of the movement of pawns and kings.

    if (board[start_x][start_y]->getType() == king)
        strcpy(king_position[player_turn], end_pos);    // Update the King's position.

    // Check if an enemy piece has been taken.
    if (board[end_x][end_y] != nullptr) {

        // Add taken pieces to taken arrays
        if (player_turn == white) {
            black_taken.push_back(board[end_x][end_y]->getType());
            black_material_val += piece_values.find(black_taken.back())->second;
        }
        else {
            white_taken.push_back(board[end_x][end_y]->getType());
            white_material_val += piece_values.find(white_taken.back())->second;
        }
        
        // sort taken arrays
        std::sort(black_taken.begin(), black_taken.end());
        std::sort(white_taken.begin(), white_taken.end());

        output_status += " capturing ";
        output_status += print_colour[board[end_x][end_y]->getColour()];
        output_status += "'s " + std::string(print_type[board[end_x][end_y]->getType()]);
        output_status += ".\n";

        // deallocate taken piece    
        delete board[end_x][end_y];
    }

    else
        output_status += ".\n";

    if (board[start_x][start_y]->getType() == pawn)     // Check if a pawn has reached the opposite edge of the board.
        if (end_y == 7 || end_y == 0)
            promotePawn(start_pos);
    
    board[end_x][end_y] = board[start_x][start_y];
    board[start_x][start_y] = nullptr;

    // Check if the move results in check for the opposing player.

    if (isInCheck(other_player_turn, king_position[other_player_turn])) {
        in_check[other_player_turn] = true;
        output_status += "\t" + std::string(print_colour[other_player_turn]);
        output_status += " is in check";
    }
    else 
        in_check[other_player_turn] = false;

    toggle(player_turn);
    outcome = checkGameOutcome();
    if (outcome == in_play && in_check[other_player_turn])
        output_status += ".\n";

    output_status += "\n";
}


bool ChessBoard::movingIntoCheck(const char* start_pos, const char* end_pos) {
    const auto start_x = start_pos[0] - 'A';
    const auto start_y = start_pos[1] - '1';
    const auto end_x = end_pos[0] - 'A';
    const auto end_y = end_pos[1] - '1';

    // Temprarily move piece
    Piece* ptr_holder = board[end_x][end_y];
    board[end_x][end_y] = board[start_x][start_y];
    board[start_x][start_y] = nullptr;

    char king_position_holder[3]; // Remember the King's previous position
    strcpy(king_position_holder, king_position[player_turn]);

    if (board[end_x][end_y]->getType() == king) // Temporarily update the King's position
        strcpy(king_position[player_turn], end_pos);

    // If player is in check undo the move and return error.
    if (isInCheck(player_turn, king_position[player_turn])) {
        board[start_x][start_y] = board[end_x][end_y];
        board[end_x][end_y] = ptr_holder;
        strcpy(king_position[player_turn], king_position_holder);
        return MOVING_INTO_CHECK;
    }

    // Undo the move and return no error.
    board[start_x][start_y] = board[end_x][end_y];
    board[end_x][end_y] = ptr_holder;
    strcpy(king_position[player_turn], king_position_holder);
    return NO_ERROR;
}


void ChessBoard::configureBoard() {
    output_status = "A new chess game is started!\n";

    // Initilise board pointers to nullptr
    for (auto rank = 2u; rank < 6; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            board[file][rank] = nullptr;
        }
    }

    // Create pieces on heap
    Colour team_identifier = white;

    for (auto i = 0u; i < 8; i += 7) {

        board[0][i] = new Rook(team_identifier);
        board[1][i] = new Knight(team_identifier);
        board[2][i] = new Bishop(team_identifier);
        board[3][i] = new Queen(team_identifier);
        board[4][i] = new King(team_identifier);
        board[5][i] = new Bishop(team_identifier);
        board[6][i] = new Knight(team_identifier);
        board[7][i] = new Rook(team_identifier);

        for(auto file = 0u; file < 8; ++file) {
            int rank_offset = ((team_identifier == white) ? (i + 1) : (i - 1)); // toggle rank offset depending on colour
            board[file][rank_offset] = new Pawn(team_identifier);
        }

        team_identifier = black;
    }

    strcpy(king_position[white],"E1");
    strcpy(king_position[black],"E8");

    player_turn = white;
    outcome = in_play;
}


bool ChessBoard::checkInput(const char* start_pos, const char* end_pos) {
    // Check Coordinates are within range
    using std::cerr;

    if (strlen(start_pos) != 2 ||
            start_pos[0] < 'A' ||
            start_pos[0] > 'H' ||
            start_pos[1] < '1' ||
            start_pos[1] > '8') {
                output_status += start_pos;
                output_status += " is in an illegal starting coordinate.\n\n";
                return false;
    }
    if (strlen(end_pos) != 2 ||
            end_pos[0] < 'A' ||
            end_pos[0] > 'H' ||
            end_pos[1] < '1' ||
            end_pos[1] > '8') {
            output_status += end_pos;
            output_status += " is in an illegal end coordinate.\n\n";
            return false;
    }
    const auto file = start_pos[0] - 'A';
    const auto rank = start_pos[1] - '1';
    if (board[file][rank] == nullptr) {
        output_status += "The starting position ";
        output_status += start_pos;
        output_status += " does not contain a piece.\n\n";
        return false;
    }
    return true;
}


void ChessBoard::displayBoard() const {
    // Displays a unicode chess board as well as material advantage.
    using namespace std;
    cout << "  ┌";
    for (auto i = 0u; i < 31; i++)
        cout <<  "—";

    for (auto rank = 7; rank >= 0; --rank) {

        if (rank == 7) {
            cout << "┐\t";

            for(auto i = 0U; i < white_taken.size(); i++)
                cout << print_unicode_symbol_white[white_taken[i]] << " ";

            if (white_material_val > black_material_val)
                cout << " +" << white_material_val - black_material_val;

            cout << "\n\t";
        }   
        cout <<rank+1 << " | ";


        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] == nullptr) 
                cout << "  | ";
            else {
                Piece* piece = board[file][rank];
                if (piece->getColour() == white)
                    cout << print_unicode_symbol_white[piece->getType()];
                else if (piece->getColour() == black)
                    cout << print_unicode_symbol_black[piece->getType()];
                else cout << "  ";
                cout << " | ";
            }
        }

        if (rank == 0)
            cout <<"\n\t  └";
        else
            cout << "\n\t  |";
        for (auto i = 0u; i < 31; i++)
            cout << "—";
        if (rank != 0)
            cout << "|\n\t";
        else 
            cout << "┘\t";
    }

    for(auto i = 0U; i < black_taken.size(); i++)
        cout << print_unicode_symbol_black[black_taken[i]] << " ";

    if (black_material_val > white_material_val)
        cout << " +" << black_material_val - white_material_val;

    cout << endl << "\t    A   B   C   D   E   F   G   H" << endl << endl;

    cout << "\t" << output_status;
}


bool ChessBoard::isInCheck(Colour current_player, const char* target) {
    // Check if any piece can make a legal move to the target position.
    Colour other_player = current_player;
    toggle(other_player);
    char test_pos[2];
    for (auto file = 0u; file < 8; ++file) {
        for (auto rank = 0u; rank < 8; ++rank) {
            if (board[file][rank] != nullptr) {
                // If the king is in check return error.
                test_pos[0] = file + 'A';
                test_pos[1] = rank + '1';
                if (board[file][rank]->isLegalMove(test_pos, target, board, other_player) == NO_ERROR) {
                    return true;
                }
            }
        }
    }
    return false;
}


void ChessBoard::clearBoard() {
    for (auto rank = 0u; rank < 8; ++rank) 
        for (auto file = 0u; file < 8; ++file)
            if (board[file][rank] != nullptr)
                delete board[file][rank];
}


bool ChessBoard::hasLegalMoves(Colour player) {
    using namespace std;
    char start_pos[2];
    char end_pos[2];
    for (int i = 'A'; i < 'I'; ++i) 
        for (int j = '1'; j < '9'; ++j) 
            for (int k = 'A'; k < 'I'; ++k) 
                for (int l = '1'; l < '9'; ++l) 
                    if (board[i - 'A'][j - '1'] != nullptr) {
                        start_pos[0] = i;
                        start_pos[1] = j;
                        end_pos[0] = k;
                        end_pos[1] = l;
                        if (board[i - 'A'][j - '1']->isLegalMove(start_pos, end_pos, board, player) == NO_ERROR)
                            if (movingIntoCheck(start_pos, end_pos) != MOVING_INTO_CHECK) 
                                return true;
                    }
    return false;
}


void ChessBoard::toggle(Colour& player_turn) {
    if (player_turn == white)
        player_turn = black;
    else
        player_turn = white;
}


bool ChessBoard::castling(const char* start_pos, const char* end_pos) {
    using std::cerr;
    using std::cout;

    if (strcmp(king_position[player_turn], start_pos))
        return false;
    
    int start_x = start_pos[0] - 'A';
    auto start_y = start_pos[1] - '1';
    auto end_x = end_pos[0] - 'A';
    auto end_y = end_pos[1] - '1';
    auto delta_x = end_x - start_x;

    if (delta_x != -2 && delta_x != 2)
        return false;

    // Assume Queen side castle.
    int rook_start_x = 0;
    auto increment = -1;

    // Case for king side castle.
    if (delta_x == 2) {
        rook_start_x = 7;
        increment = 1;
    }

    if (board[rook_start_x][start_y] == nullptr) {
        return false;}

    if (board[rook_start_x][start_y]->getColour() != player_turn)
        return false;   
    
    if (board[rook_start_x][start_y]->getType() != rook)
        return false; 

    if (board[rook_start_x][start_y]->hasMoved()) {
        output_status += "Castling is illegal because ";
        output_status += player_turn;
        output_status += "'s rook has previously moved.\n\n";
        return true;
    }

    if (board[start_x][start_y]->hasMoved()) {
        output_status += "castling is illegal because ";
        output_status += std::string(print_colour[player_turn]);
        output_status += "'s King has previously moved.\n\n";
        return true;
    }

    if (isInCheck(player_turn, king_position[player_turn])) {
        output_status += "Castling is illegal because ";
        output_status += std::string(print_colour[player_turn]);
        output_status += " is in check.\n\n";
        return true;
    }
    
    for (int i = start_x + increment; i != rook_start_x; i += increment) {
        if (board[i][start_y] != nullptr) {
            output_status += "Castling is illegal as there is a piece in the way.\n\n";
            return true;
        }
    }

    char test_pos[2];
    test_pos[1] = start_pos[1];
    for (auto i = start_pos[0]; i != (rook_start_x + 'A'); i += increment) {
        test_pos[0] = i;
        if (isInCheck(player_turn, test_pos)) {
            output_status += "Castling is illegal as the king would move through check.\n\n";
            return true;
        }
    }

    // Perform the castling move.
    strcpy(king_position[player_turn], end_pos);
    board[end_x][end_y] = board[start_x][start_y]; // Move King
    board[start_x][start_y] = nullptr;
    
    board[start_x + increment][start_y] = board[rook_start_x][start_y]; // Move Rook
    board[rook_start_x][start_y] = nullptr;


    output_status += std::string(print_colour[player_turn]);
    output_status += " performs a ";
    if (increment == -1) output_status += "queen";
    else output_status += "king";
    output_status += " side castle.\n\n";

    return true;
}


void ChessBoard::promotePawn(const char* pawn_pos) {
    auto start_x = pawn_pos[0] - 'A';
    auto start_y = pawn_pos[1] - '1';
    delete board[start_x][start_y];
    board[start_x][start_y] = new Queen(player_turn);
    output_status += "\t" + std::string(print_colour[player_turn]);
    output_status += "'s pawn has been promoted to a queen.\n\n";
}


Outcome ChessBoard::checkGameOutcome() {
    using std::cout;
    if (in_check[player_turn]) {
        if (!hasLegalMoves(player_turn)) {
            output_status += "mate.\n";
            return (player_turn == white) ? white_wins : black_wins;
        }
    }
    else {
        if (!hasLegalMoves(player_turn)) {
            output_status += "Game ends in stalemate.\n";
            return stalemate;
        }
    }
    return in_play;
}