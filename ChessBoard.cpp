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

    if(!checkInput(start_pos, end_pos)) {
        return;
    }

    if(outcome != in_play) {
        cerr << "The current game has ended, please reset the board.\n";
        return;
    }

    const auto file = start_pos[0] - 'A';
    const auto rank = start_pos[1] - '1';

    // Check if move is valid.

    int error_code = board[file][rank]->isValidMove(start_pos, end_pos, board, player_turn);

    switch (error_code) {
        case WRONG_TURN :
            cerr << "Cannot move piece, it's not " << print_colour[board[file][rank]->getColour()];
            cerr << "'s turn.\n";
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

    if (movingIntoCheck(start_pos, end_pos) == MOVING_INTO_CHECK) {
        cerr << "This move would expose " << print_colour[board[file][rank]->getColour()];
        cerr << "'s King to check.\n";
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

    board[start_x][start_y]->hasMoved();

    if (board[end_x][end_y] != nullptr) {
        cout << " taking ";
        cout << print_colour[board[end_x][end_y]->getColour()];
        cout << "'s " << print_type[board[end_x][end_y]->getType()];
        cout << std::endl;
        delete board[end_x][end_y];
    }
    else
        cout << ".\n";
    
    board[end_x][end_y] = board[start_x][start_y];
    board[start_x][start_y] = nullptr;

    displayBoard();
    outcome = checkGameOutcome();
    toggle(player_turn);
}

bool ChessBoard::movingIntoCheck(const char* start_pos, const char* end_pos) {
    using std::cout;
    // Temprarily move piece
    const auto start_x = start_pos[0] - 'A';
    const auto start_y = start_pos[1] - '1';
    const auto end_x = end_pos[0] - 'A';
    const auto end_y = end_pos[1] - '1';

    Piece* ptr_holder = board[end_x][end_y];
    board[end_x][end_y] = board[start_x][start_y];
    board[start_x][start_y] = nullptr;

    // Check if any piece can make a valid move to the current player's king's position.
    for (auto file = 0u; file < 8; ++file) {
        for (auto rank = 0u; rank < 8; ++rank) {
            if (board[file][rank] != nullptr) {
                if (!board[file][rank]->isValidMove(start_pos, king_position[player_turn], board, player_turn)) {
                    // If the king is in check, undo the move and return error.
                    board[start_x][start_y] = board[end_x][end_y];
                    board[end_x][end_y] = ptr_holder;
                    return MOVING_INTO_CHECK;
                }
            }
        }
    }
    // Undo the move and return no error.
    board[start_x][start_y] = board[end_x][end_y];
    board[end_x][end_y] = ptr_holder;
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
        board[3][i] = new King(team_identifier);
        board[4][i] = new Queen(team_identifier);
        board[5][i] = new Bishop(team_identifier);
        board[6][i] = new Knight(team_identifier);
        board[7][i] = new Rook(team_identifier);

        for(auto file = 0u; file < 8; ++file) {
            int rank_offset = ((team_identifier == white) ? (i + 1) : (i - 1)); // toggle rank offset depending on colour
            board[file][rank_offset] = new Pawn(team_identifier);
        }

        team_identifier = black;
    }

    strcpy(king_position[white],"D1");
    strcpy(king_position[black],"D8");

    displayBoard();

}

bool ChessBoard::checkInput(const char* start_pos, const char* end_pos) {
    // Check Coordinates are within range
    using std::cerr;
    if (strlen(start_pos) != 2 ||
            start_pos[0] < 'A' ||
            start_pos[0] > 'H' ||
            start_pos[1] < '1' ||
            start_pos[1] > '8') {
                cerr << start_pos << "is in an invalid starting coordinate.\n";
                return false;
    }
    if (strlen(end_pos) != 2 ||
            end_pos[0] < 'A' ||
            end_pos[0] > 'H' ||
            end_pos[1] < '1' ||
            end_pos[1] > '8') {
            cerr << end_pos << "is in an invalid end coordinate.\n";
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

    for (auto rank = 0u; rank < 8; ++rank) {
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


void ChessBoard::clearBoard() {
    for (auto rank = 0u; rank < 8; ++rank) {
        for (auto file = 0u; file < 8; ++file) {
            if (board[file][rank] != nullptr)
                delete board[file][rank];
        }
    }
}

void ChessBoard::toggle(Colour& player_turn) {
    if (player_turn == white)
        player_turn = black;
    else
        player_turn = white;
}

Outcome ChessBoard::checkGameOutcome() {
    // if checkmate return etc
    return in_play;
}