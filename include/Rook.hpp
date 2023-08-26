#ifndef ROOK_HPP
#define ROOK_HPP
#include <Piece.hpp>
namespace chess
{
    class Rook : public Piece
    {
    public:
        inline Rook(Point loc, Player player) : Piece(loc, player, PieceType::ROOK, 5)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
}
#endif