#ifndef BOTS_H
#define BOTS_H
#include "Chess.h"
#include <random>
namespace chess
{
    class RandomBot : public Bot
    {
    public:
        RandomBot() = default;
        Move* findMove(Board* board);
    };
}
#endif