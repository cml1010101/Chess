#include "../include/Chess.h"
#include <math.h>
#include <algorithm>
#include <memory.h>
#include <iostream>
#include <filesystem>
using namespace chess;
using namespace std;
bool Pawn::canMove(Board* board, Move* move)
{
    int dRow = (move->dest.row - loc.row) * direction(player), dCol = abs(move->dest.col - loc.col);
    if (dRow == 1)
    {
        if (dCol == 0)
        {
            return board->grid[move->dest.row][move->dest.col] == NULL;
        }
        else if (dCol == 1)
        {
            return board->grid[move->dest.row][move->dest.col] != NULL
                && board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dRow == 2 && dCol == 0)
    {
        return board->grid[move->dest.row][move->dest.col] == NULL
            && board->grid[move->dest.row - direction(player)][move->dest.col] == NULL
            && move->src.row == (starting_row(player) + direction(player));
    }
    return false;
}
vector<Move*> Pawn::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    move = new Move(loc, loc + Point(direction(player), 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(direction(player), 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(direction(player), -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(direction(player) * 2, 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    return moves;
}
bool Rook::canMove(Board* board, Move* move)
{
    int dRow = move->dest.row - loc.row, dCol = move->dest.col - loc.col;
    if (dRow == 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row][loc.col + i]) return false;
            }
            return board->grid[loc.row][move->dest.col] == NULL
                || board->grid[loc.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row][loc.col - i]) return false;
            }
            return board->grid[loc.row][move->dest.col] == NULL
                || board->grid[loc.row][move->dest.col]->player != player;
        }
    }
    else if (dCol == 0)
    {
        if (dRow > 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row + i][loc.col]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dRow < 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    return false;
}
vector<Move*> Rook::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    for (size_t i = 0; i < 8; i++)
    {
        move = new Move(loc, Point(i, loc.col));
        if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
        move = new Move(loc, Point(loc.row, i));
        if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    }
    return moves;
}
bool Knight::canMove(Board* board, Move* move)
{
    int dRow = abs(move->dest.row - loc.row), dCol = abs(move->dest.col - loc.col);
    return ((dRow == 1 && dCol == 2) || (dRow == 2 && dCol == 1))
        && (board->grid[move->dest.row][move->dest.col] == NULL
        || board->grid[move->dest.row][move->dest.col]->player != board->next);
}
vector<Move*> Knight::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    move = new Move(loc, loc + Point(1, 2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(1, -2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(2, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(2, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, 2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, -2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-2, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-2, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    return moves;
}
bool Bishop::canMove(Board* board, Move* move)
{
    int dRow = move->dest.row - loc.row, dCol = move->dest.col - loc.col;
    if (!(abs(dRow) == abs(dCol))) return false;
    if (dRow > 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row + i][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row + i][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dRow < 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    return false;
}
vector<Move*> Bishop::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            move = new Move(loc, Point(i, j));
            if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
        }
    }
    return moves;
}
bool Queen::canMove(Board* board, Move* move)
{
    int dRow = move->dest.row - loc.row, dCol = move->dest.col - loc.col;
    if (dRow == 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dCol == 0)
    {
        if (dRow > 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row + i][loc.col]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dRow < 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    if (!(abs(dRow) == abs(dCol))) return false;
    if (dRow > 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row + i][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dCol); i++)
            {
                if (board->grid[loc.row + i][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    else if (dRow < 0)
    {
        if (dCol > 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col + i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
        else if (dCol < 0)
        {
            for (size_t i = 1; i < abs(dRow); i++)
            {
                if (board->grid[loc.row - i][loc.col - i]) return false;
            }
            return board->grid[move->dest.row][move->dest.col] == NULL
                || board->grid[move->dest.row][move->dest.col]->player != player;
        }
    }
    return false;
}
vector<Move*> Queen::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            move = new Move(loc, Point(i, j));
            if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
        }
    }
    return moves;
}
bool King::canMove(Board* board, Move* move)
{
    int dRow = abs(move->dest.row - loc.row), dCol = abs(move->dest.col - loc.col);
    if (move->src.col == 4 && move->src.row == starting_row(player)
        && move->dest.col == 6 && move->dest.row == starting_row(player))
    {
        return move->src == (player == PLAYER_WHITE ? board->kingWhite : board->kingBlack)
            && (board->grid[move->dest.row][move->dest.col] == NULL)
            && (board->grid[starting_row(player)][5] == NULL)
            && (board->grid[starting_row(player)][6] == NULL)
            && (board->grid[starting_row(player)][7] != NULL)
            && (board->grid[starting_row(player)][7]->type == PIECE_ROOK);
    }
    if (move->src.col == 4 && move->src.row == starting_row(player)
        && move->dest.col == 2 && move->dest.row == starting_row(player))
    {
        return move->src == (player == PLAYER_WHITE ? board->kingWhite : board->kingBlack)
            && (board->grid[move->dest.row][move->dest.col] == NULL)
            && (board->grid[starting_row(player)][3] == NULL)
            && (board->grid[starting_row(player)][2] == NULL)
            && (board->grid[starting_row(player)][1] == NULL)
            && (board->grid[starting_row(player)][0] != NULL)
            && (board->grid[starting_row(player)][0]->type == PIECE_ROOK);
    }
    return (dRow == 0 || dRow == 1) && (dCol == 0 || dCol == 1)
        && (board->grid[move->dest.row][move->dest.col] == NULL
        || board->grid[move->dest.row][move->dest.col]->player != board->next);
}
vector<Move*> King::getPossibleMoves(Board* board, bool checkForCheck)
{
    vector<Move*> moves = {};
    Move* move;
    move = new Move(loc, loc + Point(1, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(1, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(1, 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(0, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(0, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, 1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, 0));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(loc, loc + Point(-1, -1));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(Point(starting_row(player), 4), Point(starting_row(player), 6));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    move = new Move(Point(starting_row(player), 4), Point(starting_row(player), 2));
    if (board->canMove(move, checkForCheck)) moves.emplace_back(move);
    return moves;
}
Board::Board()
{
    for (size_t i = 2; i < 6; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            grid[i][j] = NULL;
        }
    }
    grid[0][0] = new Rook(Point(0, 0), PLAYER_WHITE);
    grid[0][1] = new Knight(Point(0, 1), PLAYER_WHITE);
    grid[0][2] = new Bishop(Point(0, 2), PLAYER_WHITE);
    grid[0][4] = new King(Point(0, 4), PLAYER_WHITE);
    grid[0][3] = new Queen(Point(0, 3), PLAYER_WHITE);
    grid[0][5] = new Bishop(Point(0, 5), PLAYER_WHITE);
    grid[0][6] = new Knight(Point(0, 6), PLAYER_WHITE);
    grid[0][7] = new Rook(Point(0, 7), PLAYER_WHITE);
    grid[7][0] = new Rook(Point(7, 0), PLAYER_BLACK);
    grid[7][1] = new Knight(Point(7, 1), PLAYER_BLACK);
    grid[7][2] = new Bishop(Point(7, 2), PLAYER_BLACK);
    grid[7][4] = new King(Point(7, 4), PLAYER_BLACK);
    grid[7][3] = new Queen(Point(7, 3), PLAYER_BLACK);
    grid[7][5] = new Bishop(Point(7, 5), PLAYER_BLACK);
    grid[7][6] = new Knight(Point(7, 6), PLAYER_BLACK);
    grid[7][7] = new Rook(Point(7, 7), PLAYER_BLACK);
    for (size_t i = 0; i < 8; i++)
    {
        grid[1][i] = new Pawn(Point(1, i), PLAYER_WHITE);
        grid[6][i] = new Pawn(Point(6, i), PLAYER_BLACK);
    }
    next = PLAYER_WHITE;
    kingWhite = Point(0, 4);
    kingBlack = Point(7, 4);
    winner = WINNER_NONE;
}
bool Board::canMove(Move* move, bool checkForCheck)
{
    if (move->src == move->dest)
    {
        return false;
    }
    if (!(move->src) || !(move->dest))
    {
        return false;
    }
    if (grid[move->src.row][move->src.col] == NULL)
    {
        return false;
    }
    if (grid[move->src.row][move->src.col]->player != next) return false;
    if (grid[move->src.row][move->src.col]->canMove(this, move))
    {
        if (!checkForCheck) return true;
        Board* next = clone();
        next->playMove(move);
        if (next->inCheck()) return false;
        return true;
    }
    return false;
}
void Board::playMove(Move* move)
{
    if (move->isResign)
    {
        winner = (next == PLAYER_WHITE) ? WINNER_BLACK : WINNER_WHITE;
        return;
    }
    if (move->isDraw)
    {
        winner = WINNER_DRAW;
    }
    if (grid[move->src.row][move->src.col]->type == PIECE_KING)
    {
        if (move->src == Point(starting_row(next), 4) 
            && move->dest == Point(starting_row(next), 6))
        {
            grid[move->dest.row][5] = grid[move->src.row][7];
            grid[move->src.row][7] = NULL;
            grid[move->src.row][5]->loc = Point(move->src.row, 5);
        }
        else if (move->src == Point(starting_row(next), 4)
            && move->dest == Point(starting_row(next), 2))
        {
            grid[move->dest.row][3] = grid[move->src.row][0];
            grid[move->src.row][0] = NULL;
            grid[move->src.row][3]->loc = Point(move->src.row, 3);
        }
        Point& king = (next == PLAYER_WHITE) ? kingWhite : kingBlack;
        king = move->dest;
    }
    grid[move->src.row][move->src.col]->loc = move->dest;
    grid[move->dest.row][move->dest.col] = grid[move->src.row][move->src.col];
    grid[move->src.row][move->src.col] = NULL;
    if (grid[move->dest.row][move->dest.col]->type == PIECE_PAWN)
    {
        if (move->dest.row == starting_row(other(next)))
        {
            grid[move->dest.row][move->dest.col] = new Queen(move->dest, next);
        }
    }
    next = other(next);
}
vector<Piece*> Board::getPieces(Player player)
{
    vector<Piece*> pieces = {};
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j] && grid[i][j]->player == player)
            {
                pieces.emplace_back(grid[i][j]);
            }
        }
    }
    return pieces;
}
vector<Move*> Board::getPossibleMoves(bool checkForCheck)
{
    vector<Move*> moves = {};
    auto pieces = getPieces(next);
    for (auto piece : pieces)
    {
        auto possibleMoves = piece->getPossibleMoves(this, checkForCheck);
        for (auto move : possibleMoves)
        {
            moves.push_back(move);
        }
    }
    return moves;
}
bool Board::inCheck()
{
    for (auto piece : getPieces(next))
    {
        Point king = (next == PLAYER_WHITE) ? kingBlack : kingWhite;
        Move* move = new Move(piece->loc, king);
        if (canMove(move, false)) return true;
    }
    return false;
}
Board* Board::clone()
{
    Board* clone = new Board();
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j]) clone->grid[i][j] = grid[i][j]->clone();
            else clone->grid[i][j] = NULL;
        }
    }
    clone->next = next;
    clone->kingBlack = kingBlack;
    clone->kingWhite = kingWhite;
    clone->winner = winner;
    return clone;
}
Piece* Pawn::clone()
{
    return new Pawn(loc, player);
}
Piece* Rook::clone()
{
    return new Rook(loc, player);
}
Piece* Knight::clone()
{
    return new Knight(loc, player);
}
Piece* Bishop::clone()
{
    return new Bishop(loc, player);
}
Piece* Queen::clone()
{
    return new Queen(loc, player);
}
Piece* King::clone()
{
    return new King(loc, player);
}
Game::Game(Bot* whiteBot, Bot* blackBot)
{
    boards = {new Board()};
    moves = {};
    bots = {{PLAYER_WHITE, whiteBot}, {PLAYER_BLACK, blackBot}};
    whiteBot->setPlayer(PLAYER_WHITE);
    blackBot->setPlayer(PLAYER_BLACK);
    whiteBot->setGameReference(this);
    blackBot->setGameReference(this);
}
Board* Game::getCurrentBoard()
{
    return boards[boards.size() - 1];
}
void Game::playMove(Move* move)
{
    Board* nextBoard = getCurrentBoard()->clone();
    nextBoard->playMove(move);
    boards.emplace_back(nextBoard);
    moves.emplace_back(move);
}
void Game::step()
{
    if (getCurrentBoard()->isDraw())
    {
        playMove(Move::resign());
    }
    else
    {
        auto move = bots[getCurrentBoard()->next]->findMove(getCurrentBoard());
        bots[PLAYER_WHITE]->handleMove(move, getCurrentBoard());
        bots[PLAYER_BLACK]->handleMove(move, getCurrentBoard());
        playMove(move);
    }
}
ostream& operator<<(ostream& out, Board board)
{
    for (int i = 8 - 1; i >= 0; i--)
    {
        out << (i + 1) << "\t";
        for (size_t j = 0; j < 8; j++)
        {
            if (board.grid[i][j])
            {
                string letter;
                switch (board.grid[i][j]->type)
                {
                case PIECE_PAWN:
                    letter = "p";
                    break;
                case PIECE_ROOK:
                    letter = "r";
                    break;
                case PIECE_KNIGHT:
                    letter = "n";
                    break;
                case PIECE_BISHOP:
                    letter = "b";
                    break;
                case PIECE_QUEEN:
                    letter = "q";
                    break;
                case PIECE_KING:
                    letter = "k";
                    break;
                }
                if (board.grid[i][j]->player == PLAYER_BLACK)
                {
                    transform(letter.begin(), letter.end(), letter.begin(), ::toupper);
                }
                out << letter;
            }
            else out << " ";
        }
        out << endl;
    }
    out << "\tABCDEFGH\n";
    return out;
}
bool Board::isDraw()
{
    return getPieces(next).size() == 0 || getPieces(next).size() == 1;
}
double Board::getScore()
{
    double difference = 0;
    auto piecesNext = getPieces(next);
    auto piecesOther = getPieces(next == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE);
    for (auto piece : piecesNext)
    {
        difference += piece->value;
    }
    for (auto piece : piecesOther)
    {
        difference -= piece->value;
    }
    return difference;
}
double Board::getBestResult(int maxDepth)
{
    if (winner != -1)
    {
        return winner == (Winner)(int)next ? 0x1000 : -0x1000;
    }
    if (maxDepth == 0)
    {
        return getScore();
    }
    double bestSoFar = -0x1000;
    auto moves = getPossibleMoves(true);
    for (auto move : moves)
    {
        Board* nextBoard = clone();
        nextBoard->playMove(move);
        double bestResult = -nextBoard->getBestResult(maxDepth - 1);
        if (bestSoFar < bestResult) bestSoFar = bestResult;
    }
    return bestSoFar;
}
MinimaxBot::MinimaxBot(int maxDepth)
{
    this->maxDepth = maxDepth;
}
Move* MinimaxBot::findMove(Board* board)
{
    auto possibleMoves = board->getPossibleMoves(true);
    if (possibleMoves.size() == 0 || board->isDraw()) return Move::resign();
    std::vector<std::pair<double, Move*>> moveScores = {};
    for (auto move : possibleMoves)
    {
        Board* nextBoard = board->clone();
        nextBoard->playMove(move);
        moveScores.push_back({-nextBoard->getBestResult(maxDepth), move});
    }
    sort(moveScores.begin(), moveScores.end());
    double idealScore = moveScores[moveScores.size() - 1].first;
    std::vector<Move*> idealMoves = {};
    for (int i = moveScores.size() - 1; i >= 0; i--)
    {
        if (moveScores[i].first == idealScore) idealMoves.push_back(moveScores[i].second);
    }
    return idealMoves[rand() % idealMoves.size()];
}
uint8_t* Board::serialize()
{
    uint8_t* serial = new uint8_t[65];
    memset(serial, 0, 64);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j]) serial[i * 8 + j] = (1 << 7) |
                (grid[i][j]->player << 6) | grid[i][j]->type;
        }
    }
    serial[64] = next;
    return serial;
}
Board* Board::fromSerial(uint8_t* serial)
{
    Board* board = new Board();
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (serial[i * 8 + j] == 0) board->grid[i][j] = NULL;
            else
            {
                switch (serial[i * 8 + j] & 0b111)
                {
                case PIECE_PAWN:
                    board->grid[i][j] = new Pawn(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PIECE_ROOK:
                    board->grid[i][j] = new Rook(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PIECE_KNIGHT:
                    board->grid[i][j] = new Knight(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PIECE_BISHOP:
                    board->grid[i][j] = new Bishop(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PIECE_QUEEN:
                    board->grid[i][j] = new Queen(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PIECE_KING:
                    board->grid[i][j] = new King(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    ((Player)((serial[i * 8 + j] & (1 << 6)) >> 6) == PLAYER_WHITE 
                        ? board->kingWhite : board->kingBlack) = Point(i, j);
                    break;
                default:
                    break;
                }
            }
        }
    }
    board->next = (Player)serial[64];
    return board;
}
using namespace torch;
using namespace nn;
Tensor Board::encode()
{
    Tensor encoded = torch::empty({6, 8, 8});
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j]) encoded[grid[i][j]->type][i][j] = 
                grid[i][j]->player == next ? 1 : -1;
        }
    }
    return encoded;
}
NeuralBot::NeuralBot()
{
    model = Sequential(
        Conv2d(Conv2dOptions(6, 24, 3)),
        Flatten(FlattenOptions().start_dim(0).end_dim(-1)),
        Linear(LinearOptions(864, 864)),
        Sigmoid(),
        Linear(LinearOptions(864, 1)),
        Tanh()
    );
}
Move* NeuralBot::findMove(Board* board)
{
    auto moves = board->getPossibleMoves(true);
    Move* highestScoringMove;
    double highestScore = -1;
    for (auto move : moves)
    {
        Board* nextState = board->clone();
        nextState->playMove(move);
        double score = model->forward(nextState->encode()).item<double>();
        if (score > highestScore)
        {
            highestScoringMove = move;
            highestScore = score;
        }
    }
    return highestScoringMove;
}
const string TIE = "1/2-1/2";
using namespace boost;
const regex numStatement = regex("\\d."),
    moveStatement = regex("([BNKQR]?)(([a-h])?(\\d)?)(x?)([a-h]\\d)(\\+?)");
istream& operator>>(istream& in, chess::Game& game)
{
    game.boards = {new Board()};
    game.moves = {};
    string token;
    bool b = false;
    while (true)
    {
        getline(in, token);
        if (token.empty() && b) break;
        b = true;
    }
    bool comment = false;
    while (true)
    {
        if (game.getCurrentBoard()->winner != WINNER_NONE) break;
        string statement;
        getline(in, statement, ' ');
        if (statement.empty()) break;
        if ((statement.find("{") != -1) || comment)
        {
            comment = true;
            if (statement.find("}")) comment = false;
            continue;
        }
        if (statement.substr(0, 7) == "1/2-1/2")
        {
            game.getCurrentBoard()->winner == WINNER_BLACK;
            break;
        }
        if (statement.substr(0, 3) == "1-0")
        {
            game.getCurrentBoard()->winner = WINNER_WHITE;
            break;
        }
        if (statement.substr(0, 3) == "0-1")
        {
            game.getCurrentBoard()->winner = WINNER_BLACK;
            break;
        }
        if (statement == "O-O-O")
        {
            game.playMove(new Move(
                Point(starting_row(game.getCurrentBoard()->next), 4),
                Point(starting_row(game.getCurrentBoard()->next), 2)
            ));
            continue;
        }
        if (statement.find("O-O") != -1)
        {
            game.playMove(new Move(
                Point(starting_row(game.getCurrentBoard()->next), 4),
                Point(starting_row(game.getCurrentBoard()->next), 6)
            ));
            continue;
        }
        boost::smatch matchInfo;
        if (regex_match(statement, matchInfo, moveStatement))
        {
            game.playMove(Move::parse(matchInfo, game.getCurrentBoard()));
        }
    }
    return in;
}
Move* Move::parse(smatch match, Board* board)
{
    PieceType type = PIECE_PAWN;
    string typeStr = string(match[1].begin(), match[1].end());
    if (typeStr == "R")
    {
        type = PIECE_ROOK;
    }
    else if (typeStr == "N")
    {
        type = PIECE_KNIGHT;
    }
    else if (typeStr == "B")
    {
        type = PIECE_BISHOP;
    }
    else if (typeStr == "Q")
    {
        type = PIECE_QUEEN;
    }
    else if (typeStr == "K")
    {
        type = PIECE_KING;
    }
    string srcRowStr = string(match[4].begin(), match[4].end());
    int srcRow = srcRowStr.empty() ? -1 : srcRowStr[0] - '1';
    string srcColStr = string(match[3].begin(), match[3].end());
    int srcCol = srcColStr.empty() ? -1 : srcColStr[0] - 'a';
    string destStr = string(match[6].begin(), match[6].end());
    Point dest = Point::parse(destStr);
    auto possiblePieces = board->getPieces(board->next, type);
    for (auto piece : possiblePieces)
    {
        if (piece->loc.col != srcCol && srcCol != -1) continue;
        if (piece->loc.row != srcRow && srcRow != -1) continue;
        Move* move = new Move(piece->loc, dest);
        if (board->canMove(move)) return move;
    }
    return NULL;
}
vector<Piece*> Board::getPieces(Player player, PieceType type)
{
    vector<Piece*> pieces;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j] && grid[i][j]->player == player && grid[i][j]->type == type)
                pieces.push_back(grid[i][j]);
        }
    }
    return pieces;
}
string Game::toPGN()
{
    stringstream stream;
    stream << "[Event \"None\"]\n";
    stream << "[Site \"Unknown\"]\n";
    stream << "[Date \"2000.01.01\"]\n";
    stream << "[Round \"" << moves.size() << "\"]\n";
    stream << "[White \"Unknown\"]\n";
    stream << "[Black \"Unknown\"]\n";
    string result = "*";
    switch (getCurrentBoard()->winner)
    {
    case WINNER_DRAW:
        result = "1/2-1/2";
        break;
    case WINNER_WHITE:
        result = "1-0";
        break;
    case WINNER_BLACK:
        result = "0-1";
        break;
    default:
        break;
    }
    stream << "[Result \"" << result << "\"]\n";
    return stream.str();
}
string Move::toSAN(Board* board)
{
    if (isResign)
    {
        if (board->next == PLAYER_WHITE) return "1-0";
        return "0-1";
    }
    else if (isDraw)
    {
        return "1/2-1/2";
    }
    string typeStr = "";
    PieceType type = board->grid[src.row][src.col]->type;
    if (type == PIECE_ROOK)
    {
        typeStr = "R";
    }
    if (type == PIECE_KNIGHT)
    {
        typeStr = "N";
    }
    if (type == PIECE_BISHOP)
    {
        typeStr = "B";
    }
    if (type == PIECE_QUEEN)
    {
        typeStr = "Q";
    }
    if (type == PIECE_KING)
    {
        typeStr = "K";
    }
    string captureStr = board->grid[dest.row][dest.col] ? "x" : "";
    string rowStr = "";
    string colStr = "";
    auto similarPieces = board->getPieces(board->next, type);
    for (auto piece : similarPieces)
    {
        if (piece->loc == src) continue;
        Move* move = new Move(piece->loc, dest);
        if (board->canMove(move))
        {
            if (piece->loc.col == src.col)
            {
                rowStr = to_string(piece->loc.row);
            }
            else
            {
                colStr = 'a' + piece->loc.col;
            }
        }
    }
    string checkString = "";
    Board* next = board->clone();
    next->playMove(this);
    if (next->inCheck())
    {
        if (next->isDraw())
        {
            checkString = "#";
        }
        else
        {
            checkString = "+";
        }
    }
    return typeStr + colStr + rowStr + captureStr + (string)dest + checkString;
}