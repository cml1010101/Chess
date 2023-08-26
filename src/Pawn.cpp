#include <Pawn.hpp>
#include <Board.hpp>
using namespace chess;
using namespace std;
bool Pawn::canMove(Board* board, Move* move)
{
    int dRow = (move->dest.row - loc.row) * direction(player), dCol = abs(move->dest.col - loc.col);
    if (dRow == 1)
    {
        if (dCol == 0)
        {
            return board->grid[move->dest.row][move->dest.col] == NULL;
        }
        else if (dCol == 1)
        {
            if (board->grid[move->dest.row][move->dest.col] == NULL)
            {
                return board->grid[move->src.row][move->dest.col] != NULL
                    && board->grid[move->src.row][move->dest.col]->player != player
                    && board->grid[move->src.row][move->dest.col]->type == PieceType::PAWN
                    && board->previousMove->src.col == move->dest.col
                    && board->previousMove->src.row == 
                        (starting_row(other(player)) - direction(player))
                    && board->previousMove->dest.col == move->dest.col
                    && board->previousMove->dest.row ==
                        (starting_row(other(player)) - direction(player) * 3);
            }
            return board->grid[move->dest.row][move->dest.col] != NULL
                && board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dRow == 2 && dCol == 0)
    {
        return board->grid[move->dest.row][move->dest.col] == NULL
            && board->grid[move->dest.row - direction(player)][move->dest.col] == NULL
            && move->src.row == (starting_row(player) + direction(player));
    }
    return false;
}
vector<Move*> Pawn::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    move = new Move(loc, loc + Point(direction(player), 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(direction(player), 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(direction(player), -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(direction(player) * 2, 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    return moves;
}
Piece* Pawn::clone()
{
    return new Pawn(loc, player);
}