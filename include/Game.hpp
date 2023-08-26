#ifndef GAME_HPP
#define GAME_HPP
#include <Board.hpp>
#include <Bot.hpp>
namespace chess
{
    class Game
    {
    public:
        std::vector<Board*> boards;
        std::vector<Move*> moves;
        std::map<Player, Bot*> bots;
        Game() = default;
        Game(Bot* whiteBot, Bot* blackBot);
        Board* getCurrentBoard();
        void playMove(Move* move);
        void step();
        std::string toPGN();
    };
}
#endif