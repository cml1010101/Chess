#include <King.hpp>
#include <Board.hpp>
using namespace chess;
using namespace std;
bool King::canMove(Board* board, Move* move)
{
    int dRow = abs(move->dest.row - loc.row), dCol = abs(move->dest.col - loc.col);
    if (move->src.col == 4 && move->src.row == starting_row(player)
        && move->dest.col == 6 && move->dest.row == starting_row(player))
    {
        return move->src == (player == Player::WHITE ? board->kingWhite : board->kingBlack)
            && (board->grid[move->dest.row][move->dest.col] == NULL)
            && (board->grid[starting_row(player)][5] == NULL)
            && (board->grid[starting_row(player)][6] == NULL)
            && (board->grid[starting_row(player)][7] != NULL)
            && (board->grid[starting_row(player)][7]->type == PieceType::ROOK);
    }
    if (move->src.col == 4 && move->src.row == starting_row(player)
        && move->dest.col == 2 && move->dest.row == starting_row(player))
    {
        return move->src == (player == Player::WHITE ? board->kingWhite : board->kingBlack)
            && (board->grid[move->dest.row][move->dest.col] == NULL)
            && (board->grid[starting_row(player)][3] == NULL)
            && (board->grid[starting_row(player)][2] == NULL)
            && (board->grid[starting_row(player)][1] == NULL)
            && (board->grid[starting_row(player)][0] != NULL)
            && (board->grid[starting_row(player)][0]->type == PieceType::ROOK);
    }
    return (dRow == 0 || dRow == 1) && (dCol == 0 || dCol == 1)
        && (board->grid[move->dest.row][move->dest.col] == NULL
        || board->grid[move->dest.row][move->dest.col]->player != board->next);
}
vector<Move*> King::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    move = new Move(loc, loc + Point(1, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(1, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(1, 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(0, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(0, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(Point(starting_row(player), 4), Point(starting_row(player), 6));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(Point(starting_row(player), 4), Point(starting_row(player), 2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    return moves;
}
Piece* King::clone()
{
    return new King(loc, player);
}