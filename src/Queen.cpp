#include <Queen.hpp>
#include <Board.hpp>
using namespace chess;
using namespace std;
bool Queen::canMove(Board* board, Move* move)
{
    int dRow = move->dest.row - loc.row, dCol = move->dest.col - loc.col;
    if (dRow == 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dCol == 0)
    {
        if (dRow > 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row + i][loc.col]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dRow < 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    if (!(abs(dRow) == abs(dCol))) return false;
    if (dRow > 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row + i][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row + i][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dRow < 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    return false;
}
vector<Move*> Queen::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            move = new Move(loc, Point(i, j));
            if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
        }
    }
    return moves;
}
Piece* Queen::clone()
{
    return new Queen(loc, player);
}