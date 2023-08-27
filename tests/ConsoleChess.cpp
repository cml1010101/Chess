#include <Game.hpp>
#include <Bot.hpp>
#include <iostream>
using namespace std;
using namespace chess;
const string cols = "ABCDEFGH";
class RandomBot : public Bot
{
public:
    RandomBot()
    {
        srand(time(NULL));
    }
    virtual Move* findMove(Board* board) override
    {
        vector<Move*> possibleMoves = {};
        auto pieces = board->getPieces(board->next);
        for (auto piece : pieces)
        {
            auto moves = piece->getPossibleMoves(board);
            for (auto move : moves)
            {
                possibleMoves.push_back(move);
            }
        }
        if (possibleMoves.size() == 0 || board->isDraw()) return Move::resign();
        return possibleMoves[rand() % possibleMoves.size()];
    }
};
class PlayerBot : public Bot
{
public:
    PlayerBot() = default;
    virtual Move* findMove(Board* board) override
    {
        if (board->isDraw()) return Move::resign();
        cout << "Please enter your move in format [A1 B2]: ";
        string token;
        getline(cin, token);
        if (token == "resign")
        {
            return Move::resign();
        }
        int srcCol = cols.find(token[0]);
        int srcRow = token[1] - '1';
        int destCol = cols.find(token[3]);
        int destRow = token[4] - '1';
        Move* move = new Move(Point(srcRow, srcCol), Point(destRow, destCol));
        if (!board->canMove(move))
        {
            cout << "Invalid move.\n";
            return findMove(board);
        }
        return move;
    }
};
int main(int argc, const char** argv)
{
    Game game = Game(new PlayerBot(), new RandomBot());
    while (game.getCurrentBoard()->winner == Winner::NONE)
    {
        cout << *game.getCurrentBoard() << endl;
        game.step();
    }
    return 0;
}