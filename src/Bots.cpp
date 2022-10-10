#include "../include/Bots.h"
using namespace std;
using namespace chess;
Move* RandomBot::findMove(Board* board)
{
    auto possibleMoves = board->getPossibleMoves();
    if (possibleMoves.size()) return possibleMoves[rand() % possibleMoves.size()];
    else return Move::resign();
}