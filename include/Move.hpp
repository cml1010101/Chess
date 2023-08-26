#ifndef MOVE_HPP
#define MOVE_HPP
#include <Point.hpp>
#ifdef HAVE_TORCH
#include <torch/torch.h>
#endif
#include <boost/regex.hpp>
namespace chess
{
    class Board;
    class Move
    {
    public:
        Point src, dest;
        bool isResign, isDraw;
        Move() = default;
        inline Move(Point src, Point dest, bool isResign = false, bool isDraw = false)
        {
            this->src = src;
            this->dest = dest;
            this->isResign = isResign;
            this->isDraw = isDraw;
        }
        inline static Move* resign()
        {
            return new Move({-1, -1}, {-1, -1}, true);
        }
        inline static Move* draw()
        {
            return new Move({-1, -1}, {-1, -1}, false, true);
        }
        static Move* parse(boost::smatch match, Board*);
        std::string toSAN(Board* board);
#ifdef HAVE_TORCH
        torch::Tensor encode();
        static Move* decode(torch::Tensor tensor);
#endif
    };
}
#endif