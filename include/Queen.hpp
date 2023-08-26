#ifndef QUEEN_HPP
#define QUEEN_HPP
#include <Piece.hpp>
namespace chess
{
    class Queen : public Piece
    {
    public:
        inline Queen(Point loc, Player player) : Piece(loc, player, PieceType::QUEEN, 9)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
}
#endif