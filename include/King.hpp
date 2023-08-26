#ifndef KING_HPP
#define KING_HPP
#include <Piece.hpp>
namespace chess
{
    class King : public Piece
    {
    public:
        inline King(Point loc, Player player) : Piece(loc, player, PieceType::KING, 0)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
}
#endif