#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include <Piece.hpp>
namespace chess
{
    class Knight : public Piece
    {
    public:
        inline Knight(Point loc, Player player) : Piece(loc, player, PieceType::KNIGHT, 3)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
}
#endif