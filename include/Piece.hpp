#ifndef PIECE_HPP
#define PIECE_HPP
#include <Point.hpp>
#include <Player.hpp>
#include <PieceType.hpp>
#include <Move.hpp>
namespace chess
{
    class Board;
    class Piece
    {
    public:
        PieceType type;
        Point loc;
        double value;
        Player player;
        Piece() = default;
        inline Piece(Point loc, Player player, PieceType type, double value)
        {
            this->loc = loc;
            this->player = player;
            this->type = type;
            this->value = value;
        }
        virtual bool canMove(Board* board, Move* move) = 0;
        virtual std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true) = 0;
        virtual Piece* clone() = 0;
    };
}
#endif