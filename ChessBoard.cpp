#include "ChessBoard.h"

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


void ChessBoard::submitMove(const char* start_pos, const char* end_pos) {
    using std::cerr;
    using std::cout;

    Colour other_player_turn = player_turn;
    toggle(other_player_turn);

    if(!checkInput(start_pos, end_pos)) {
        return;
    }

    if(outcome != in_play) {
        cerr << "The current game has ended, please reset the board.\n";
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
            cerr << "Cannot move piece, it's not " << print_colour[board[file][rank]->getColour()];
            cerr << "'s turn.\n";
            return;
        case SAME_START_AND_END_SQUARE :
            cerr << "The start square " << start_pos; 
            cerr << " is the same as the end square " << end_pos << ".\n";
            return;
        case OCCUPIED_SQUARE :
            cerr << end_pos << " is occupied by a friendly piece.\n";
            return;
        case INVALID_MOVEMENT :
            cerr << print_colour[board[file][rank]->getColour()];
            cerr << "'s " << print_type[board[file][rank]->getType()];
            cerr << " cannot move from " << start_pos << " to ";
            cerr << end_pos << ".\n";
            return;
        case NO_LINE_OF_SIGHT :
            cerr << print_colour[board[file][rank]->getColour()];
            cerr << "'s " << print_type[board[file][rank]->getType()];
            cerr << " cannot move from " << start_pos << " to ";
            cerr << end_pos << " as there is a piece in the way.\n";
            return;
    }
    
    // Check if the move results in the mover's king being in check.
    if (movingIntoCheck(start_pos, end_pos) == MOVING_INTO_CHECK) {
        if (in_check[player_turn]) {
            cerr << "Moving " << print_colour[player_turn];
            cerr << "'s " << print_type[board[file][rank]->getType()];
            cerr << " from " << start_pos << " to " << end_pos;
            cerr << " is illegal because " << print_colour[player_turn] << " is in check.\n";

        }
        else {
            cerr << "Moving " << print_colour[board[file][rank]->getColour()];
            cerr << "'s " << print_type[board[file][rank]->getType()];
            cerr << " from " << start_pos << " to " << end_pos;
            cerr << " would expose " << print_colour[board[file][rank]->getColour()];
            cerr << "'s King to check.\n";
        }
        return;

    }
    // Move piece.
    const auto& start_x = file;
    const auto& start_y = rank;
    const auto end_x = end_pos[0] - 'A';
    const auto end_y = end_pos[1] - '1';

    cout << print_colour[board[file][rank]->getColour()];
    cout << "'s " << print_type[board[file][rank]->getType()];
    cout << " moves from " << start_pos << " to " << end_pos;

    board[start_x][start_y]->moved();    // Used to keep track of the movement of pawns and kings.

    if (board[start_x][start_y]->getType() == king)
        strcpy(king_position[player_turn], end_pos);    // Update the King's position.

    // Check if an enemy piece has been taken.
    if (board[end_x][end_y] != nullptr) {
        cout << " taking ";
        cout << print_colour[board[end_x][end_y]->getColour()];
        cout << "'s " << print_type[board[end_x][end_y]->getType()];
        cout << ".\n";
        delete board[end_x][end_y];
    }
    else
        cout << ".\n";

    if (board[start_x][start_y]->getType() == pawn)     // Check if a pawn has reached the opposite edge of the board.
        if (end_y == 7 || end_y == 0)
            promotePawn(start_pos);
    
    board[end_x][end_y] = board[start_x][start_y];
    board[start_x][start_y] = nullptr;

    // Check if the move results in check for the opposing player.

    if (isInCheck(other_player_turn, king_position[other_player_turn])) {
        in_check[other_player_turn] = true;
        has_been_in_check[other_player_turn] = true;
        cout << print_colour[other_player_turn] << " is in check";
    }
    else 
        in_check[other_player_turn] = false;

    toggle(player_turn);
    outcome = checkGameOutcome();
    if (outcome == in_play && in_check[other_player_turn])
        cout << ".\n";

    //displayBoard();
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
    std::cout << "A new chess game is started!\n";

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
    has_been_in_check[white] = false;
    has_been_in_check[black] = false;
}


bool ChessBoard::checkInput(const char* start_pos, const char* end_pos) {
    // Check Coordinates are within range
    using std::cerr;
    if (strlen(start_pos) != 2 ||
            start_pos[0] < 'A' ||
            start_pos[0] > 'H' ||
            start_pos[1] < '1' ||
            start_pos[1] > '8') {
                cerr << start_pos << " is in an illegal starting coordinate.\n";
                return false;
    }
    if (strlen(end_pos) != 2 ||
            end_pos[0] < 'A' ||
            end_pos[0] > 'H' ||
            end_pos[1] < '1' ||
            end_pos[1] > '8') {
            cerr << end_pos << " is in an illegal end coordinate.\n";
            return false;
    }
    const auto file = start_pos[0] - 'A';
    const auto rank = start_pos[1] - '1';
    if (board[file][rank] == nullptr) {
        cerr << "The starting position " << start_pos << " does not contain a piece.\n";
        return false;
    }
    return true;
}


void ChessBoard::displayBoard() const {
    using namespace std;

    for (auto i = 0u; i < 185; i++)
        cout << "_";
    cout << "\n\n\n";

    for (auto rank = 7; rank >= 0; --rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] == nullptr) 
                cout << "\t\t|\t";
            else {
                Piece* piece = board[file][rank];
                cout << print_colour[piece->getColour()] << " ";
                cout << print_type[piece->getType()] << "\t|\t";
            }
        }
        cout << "\n\n";
        for (auto i = 0u; i < 185; i++)
            cout << "_";
        cout << "\n\n\n";
    }
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
    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] != nullptr)
                delete board[file][rank];
        }
    }
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
        cerr << "Castling is illegal because " << player_turn << "'s rook has previously moved.\n";
        return true;
    }

    if (board[start_x][start_y]->hasMoved()) {
        cerr << "castling is illegal because " << print_colour[player_turn] << "'s King has previously moved.\n";
        return true;
    }

    if (isInCheck(player_turn, king_position[player_turn])) {
        cerr << "Castling is illegal because " << print_colour[player_turn] << " is in check.\n";
        return true;
    }

    if (has_been_in_check[player_turn]) {
        cerr << "Castling is illegal because " << print_colour[player_turn] << " has previously been in check.\n";
        return true;
    }
    
    for (int i = start_x + increment; i != rook_start_x; i += increment) {
        if (board[i][start_y] != nullptr) {
            cerr << "Castling is illegal as there is a piece in the way.\n";
            return true;
        }
    }

    char test_pos[2];
    test_pos[1] = start_pos[1];
    for (auto i = start_pos[0]; i != (rook_start_x + 'A'); i += increment) {
        test_pos[0] = i;
        if (isInCheck(player_turn, test_pos)) {
            cerr << "Castling is illegal as the king would move through check.\n";
            return true;
        }
    }

    // Perform the castling move.
    strcpy(king_position[player_turn], end_pos);
    board[end_x][end_y] = board[start_x][start_y]; // Move King
    board[start_x][start_y] = nullptr;
    
    board[start_x + increment][start_y] = board[rook_start_x][start_y]; // Move Rook
    board[rook_start_x][start_y] = nullptr;


    cout << print_colour[player_turn] << " performs a ";
    if (increment == -1) cout << "queen";
    else cout << "king";
    cout << " side castle.\n";

    return true;
}


void ChessBoard::promotePawn(const char* pawn_pos) {
    auto start_x = pawn_pos[0] - 'A';
    auto start_y = pawn_pos[1] - '1';
    delete board[start_x][start_y];
    board[start_x][start_y] = new Queen(player_turn);
    std::cout << print_colour[player_turn] << "'s pawn has been promoted to a queen.\n";
}


Outcome ChessBoard::checkGameOutcome() {
    using std::cout;
    if (in_check[player_turn]) {
        if (!hasLegalMoves(player_turn)) {
            cout << "mate.\n";
            return (player_turn == white) ? white_wins : black_wins;
        }
    }
    else {
        if (!hasLegalMoves(player_turn)) {
            cout << "Game ends in stalemate.\n";
            return stalemate;
        }
    }
    return in_play;
}