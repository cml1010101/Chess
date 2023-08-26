#ifndef BOARD_HPP
#define BOARD_HPP
#include <Player.hpp>
#include <Piece.hpp>
#include <Point.hpp>
#include <Winner.hpp>
namespace chess
{
    class Board
    {
    public:
        Move* previousMove;
        Piece* grid[8][8];
        Player next;
        Point kingWhite, kingBlack;
        Winner winner;
        Board();
        bool canMove(Move* move, bool checkForCheck = true);
        void playMove(Move* move);
        std::vector<Piece*> getPieces(Player player);
        std::vector<Piece*> getPieces(Player player, PieceType type);
        std::vector<Move*> getPossibleMoves(bool checkForCheck = true);
        bool inCheck();
        bool isDraw();
        Board* clone();
        double getScore();
        double getBestResult(int maxDepth);
        uint8_t* serialize();
        static Board* fromSerial(uint8_t* serial);
#ifdef HAVE_TORCH
        torch::Tensor encode();
#endif
    };
}
#endif