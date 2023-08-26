#ifndef PAWN_HPP
#define PAWN_HPP
#include <Piece.hpp>
namespace chess
{
    class Pawn : public Piece
    {
    public:
        inline Pawn(Point loc, Player player) : Piece(loc, player, PieceType::PAWN, 1)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
}
#endif