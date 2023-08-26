#ifndef BISHOP_HPP
#define BISHOP_HPP
#include <Piece.hpp>
namespace chess
{
    class Bishop : public Piece
    {
    public:
        inline Bishop(Point loc, Player player) : Piece(loc, player, PieceType::BISHOP, 3)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
}
#endif