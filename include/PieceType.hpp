#ifndef PIECETYPE_HPP
#define PIECETYPE_HPP
namespace chess
{
    enum struct PieceType : int
    {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };
}
#endif