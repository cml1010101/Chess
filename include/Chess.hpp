#ifndef CHESS_H
#define CHESS_H
#include <Player.hpp>
#include <Winner.hpp>
#include <Point.hpp>
#include <Move.hpp>
#include <PieceType.hpp>
#include <Piece.hpp>
#include <Board.hpp>
#include <Bot.hpp>
#include <Game.hpp>
#include <map>
#include <ostream>
#ifdef HAVE_TORCH
#include <torch/torch.h>
#endif
#include <boost/regex.hpp>
namespace chess
{
}
std::ostream& operator<<(std::ostream& out, chess::Board board);
std::istream& operator>>(std::istream& in, chess::Game& game);
std::ostream& operator<<(std::ostream& out, chess::Game game);
std::ostream& operator<<(std::ostream& out, chess::Point point);
#endif