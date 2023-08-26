#ifndef WINNER_HPP
#define WINNER_HPP
namespace chess
{
    enum struct Winner : int
    {
        WHITE = 0,
        BLACK = 1,
        DRAW = 2,
        NONE = -1
    };
    
}
#endif