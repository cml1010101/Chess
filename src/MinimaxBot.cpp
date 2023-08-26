#include <MinimaxBot.hpp>
using namespace chess;
using namespace std;
MinimaxBot::MinimaxBot(int maxDepth)
{
    this->maxDepth = maxDepth;
}
Move* MinimaxBot::findMove(Board* board)
{
    auto possibleMoves = board->getPossibleMoves(true);
    if (possibleMoves.size() == 0 || board->isDraw()) return Move::resign();
    std::vector<std::pair<double, Move*>> moveScores = {};
    for (auto move : possibleMoves)
    {
        Board* nextBoard = board->clone();
        nextBoard->playMove(move);
        moveScores.push_back({-nextBoard->getBestResult(maxDepth), move});
    }
    sort(moveScores.begin(), moveScores.end());
    double idealScore = moveScores[moveScores.size() - 1].first;
    std::vector<Move*> idealMoves = {};
    for (int i = moveScores.size() - 1; i >= 0; i--)
    {
        if (moveScores[i].first == idealScore) idealMoves.push_back(moveScores[i].second);
    }
    return idealMoves[rand() % idealMoves.size()];
}