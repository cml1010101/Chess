#include <Knight.hpp>
#include <Board.hpp>
using namespace chess;
using namespace std;
bool Knight::canMove(Board* board, Move* move)
{
    int dRow = abs(move->dest.row - loc.row), dCol = abs(move->dest.col - loc.col);
    return ((dRow == 1 && dCol == 2) || (dRow == 2 && dCol == 1))
        && (board->grid[move->dest.row][move->dest.col] == NULL
        || board->grid[move->dest.row][move->dest.col]->player != board->next);
}
vector<Move*> Knight::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    move = new Move(loc, loc + Point(1, 2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(1, -2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(2, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(2, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, 2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, -2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-2, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-2, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    return moves;
}
Piece* Knight::clone()
{
    return new Knight(loc, player);
}