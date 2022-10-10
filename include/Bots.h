#ifndef BOTS_H
#define BOTS_H
#include "Chess.h"
#include <random>
namespace chess
{
    class RandomBot : public Bot
    {
    public:
        inline RandomBot(unsigned long seed = 54321)
        {
            srand(seed);
        }
        Move* findMove(Board* board);
    };
}
#endif