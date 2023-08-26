#ifndef BOT_HPP
#define BOT_HPP
#include <Board.hpp>
namespace chess
{
    class Game;
    class Bot
    {
    public:
        Bot() = default;
        virtual Move* findMove(Board* board) = 0;
        virtual void handlePrint(Board* board)
        {
        }
        virtual void handleWinner(Winner winner)
        {
        }
        virtual void setPlayer(Player player)
        {
        }
        virtual void setGameReference(Game* gameReference)
        {
        }
        virtual void handleMove(Move* move, Board* board)
        {
        }
    };
}
#endif