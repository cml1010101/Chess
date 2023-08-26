#include <Game.hpp>
#include <sstream>
using namespace chess;
using namespace std;
Game::Game(Bot* whiteBot, Bot* blackBot)
{
    boards = {new Board()};
    moves = {};
    bots = {{Player::WHITE, whiteBot}, {Player::BLACK, blackBot}};
    whiteBot->setPlayer(Player::WHITE);
    blackBot->setPlayer(Player::BLACK);
    whiteBot->setGameReference(this);
    blackBot->setGameReference(this);
}
Board* Game::getCurrentBoard()
{
    return boards[boards.size() - 1];
}
void Game::playMove(Move* move)
{
    Board* nextBoard = getCurrentBoard()->clone();
    nextBoard->playMove(move);
    boards.emplace_back(nextBoard);
    moves.emplace_back(move);
}
void Game::step()
{
    if (getCurrentBoard()->isDraw())
    {
        playMove(Move::resign());
    }
    else
    {
        auto move = bots[getCurrentBoard()->next]->findMove(getCurrentBoard());
        bots[Player::WHITE]->handleMove(move, getCurrentBoard());
        bots[Player::BLACK]->handleMove(move, getCurrentBoard());
        playMove(move);
    }
}
const string TIE = "1/2-1/2";
using namespace boost;
const regex numStatement = regex("\\d."),
    moveStatement = regex("([BNKQR]?)(([a-h])?(\\d)?)(x?)([a-h]\\d)(\\+?)");
istream& operator>>(istream& in, chess::Game& game)
{
    game.boards = {new Board()};
    game.moves = {};
    string token;
    bool b = false;
    while (true)
    {
        getline(in, token);
        if (token.empty() && b) break;
        b = true;
    }
    bool comment = false;
    while (true)
    {
        if (game.getCurrentBoard()->winner != Winner::NONE) break;
        string statement;
        getline(in, statement, ' ');
        if (statement.empty()) break;
        if ((statement.find("{") != -1) || comment)
        {
            comment = true;
            if (statement.find("}")) comment = false;
            continue;
        }
        if (statement.substr(0, 7) == "1/2-1/2")
        {
            game.getCurrentBoard()->winner == Winner::DRAW;
            break;
        }
        if (statement.substr(0, 3) == "1-0")
        {
            game.getCurrentBoard()->winner = Winner::WHITE;
            break;
        }
        if (statement.substr(0, 3) == "0-1")
        {
            game.getCurrentBoard()->winner = Winner::BLACK;
            break;
        }
        if (statement == "O-O-O")
        {
            game.playMove(new Move(
                Point(starting_row(game.getCurrentBoard()->next), 4),
                Point(starting_row(game.getCurrentBoard()->next), 2)
            ));
            continue;
        }
        if (statement.find("O-O") != -1)
        {
            game.playMove(new Move(
                Point(starting_row(game.getCurrentBoard()->next), 4),
                Point(starting_row(game.getCurrentBoard()->next), 6)
            ));
            continue;
        }
        if (statement.find(".") != -1)
        {
            continue;
        }
        boost::smatch matchInfo;
        if (regex_match(statement, matchInfo, moveStatement))
        {
            game.playMove(Move::parse(matchInfo, game.getCurrentBoard()));
        }
    }
    return in;
}
string Game::toPGN()
{
    stringstream stream;
    stream << "[Event \"None\"]\n";
    stream << "[Site \"Unknown\"]\n";
    stream << "[Date \"2000.01.01\"]\n";
    stream << "[Round \"" << moves.size() << "\"]\n";
    stream << "[White \"Unknown\"]\n";
    stream << "[Black \"Unknown\"]\n";
    string result = "*";
    switch (getCurrentBoard()->winner)
    {
    case Winner::DRAW:
        result = "1/2-1/2";
        break;
    case Winner::WHITE:
        result = "1-0";
        break;
    case Winner::BLACK:
        result = "0-1";
        break;
    default:
        break;
    }
    stream << "[Result \"" << result << "\"]\n";
    return stream.str();
}