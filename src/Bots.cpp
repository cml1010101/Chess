#include "../include/Bots.h"
#include <iostream>
using namespace std;
using namespace chess;
Move* RandomBot::findMove(Board* board)
{
    auto possibleMoves = board->getPossibleMoves();
    cout << possibleMoves.size();
    if (possibleMoves.size()) return possibleMoves[rand() % possibleMoves.size()];
    else return Move::resign();
}