#ifndef MINIMAXBOT_HPP
#define MINIMAXBOT_HPP
#include <Bot.hpp>
namespace chess
{
    class MinimaxBot : public Bot
    {
    private:
        int maxDepth;
    public:
        MinimaxBot(int maxDepth);
        Move* findMove(Board* board);
    };
}
#endif