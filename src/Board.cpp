#include <Board.hpp>
#include <Rook.hpp>
#include <Knight.hpp>
#include <Bishop.hpp>
#include <King.hpp>
#include <Queen.hpp>
#include <Pawn.hpp>
using namespace chess;
using namespace std;
Board::Board()
{
    for (size_t i = 2; i < 6; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            grid[i][j] = NULL;
        }
    }
    grid[0][0] = new Rook(Point(0, 0), Player::WHITE);
    grid[0][1] = new Knight(Point(0, 1), Player::WHITE);
    grid[0][2] = new Bishop(Point(0, 2), Player::WHITE);
    grid[0][4] = new King(Point(0, 4), Player::WHITE);
    grid[0][3] = new Queen(Point(0, 3), Player::WHITE);
    grid[0][5] = new Bishop(Point(0, 5), Player::WHITE);
    grid[0][6] = new Knight(Point(0, 6), Player::WHITE);
    grid[0][7] = new Rook(Point(0, 7), Player::WHITE);
    grid[7][0] = new Rook(Point(7, 0), Player::BLACK);
    grid[7][1] = new Knight(Point(7, 1), Player::BLACK);
    grid[7][2] = new Bishop(Point(7, 2), Player::BLACK);
    grid[7][4] = new King(Point(7, 4), Player::BLACK);
    grid[7][3] = new Queen(Point(7, 3), Player::BLACK);
    grid[7][5] = new Bishop(Point(7, 5), Player::BLACK);
    grid[7][6] = new Knight(Point(7, 6), Player::BLACK);
    grid[7][7] = new Rook(Point(7, 7), Player::BLACK);
    for (size_t i = 0; i < 8; i++)
    {
        grid[1][i] = new Pawn(Point(1, i), Player::WHITE);
        grid[6][i] = new Pawn(Point(6, i), Player::BLACK);
    }
    next = Player::WHITE;
    kingWhite = Point(0, 4);
    kingBlack = Point(7, 4);
    winner = Winner::NONE;
    previousMove = NULL;
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
    previousMove = move;
    if (move->isResign)
    {
        winner = (next == Player::WHITE) ? Winner::BLACK : Winner::WHITE;
        return;
    }
    if (move->isDraw)
    {
        winner = Winner::DRAW;
    }
    if (grid[move->src.row][move->src.col]->type == PieceType::KING)
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
        Point& king = (next == Player::WHITE) ? kingWhite : kingBlack;
        king = move->dest;
    }
    if (grid[move->src.row][move->src.col]->type == PieceType::PAWN)
    {
        int dRow = (move->dest.row - move->src.row) * direction(next),
            dCol = abs(move->dest.col - move->src.col);
        if (dRow == 1 && dCol == 1 && grid[move->dest.row][move->dest.col] == NULL
            && grid[move->src.row][move->dest.col] != NULL
            && grid[move->src.row][move->dest.col]->player != next)
        {
            grid[move->src.row][move->dest.row] = NULL;
        }
    }
    grid[move->src.row][move->src.col]->loc = move->dest;
    grid[move->dest.row][move->dest.col] = grid[move->src.row][move->src.col];
    grid[move->src.row][move->src.col] = NULL;
    if (grid[move->dest.row][move->dest.col]->type == PieceType::PAWN)
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
        Point king = (next == Player::WHITE) ? kingBlack : kingWhite;
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
                case PieceType::PAWN:
                    letter = "p";
                    break;
                case PieceType::ROOK:
                    letter = "r";
                    break;
                case PieceType::KNIGHT:
                    letter = "n";
                    break;
                case PieceType::BISHOP:
                    letter = "b";
                    break;
                case PieceType::QUEEN:
                    letter = "q";
                    break;
                case PieceType::KING:
                    letter = "k";
                    break;
                }
                if (board.grid[i][j]->player == Player::BLACK)
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
    auto piecesOther = getPieces(next == Player::WHITE ? Player::BLACK : Player::WHITE);
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
    if (winner != Winner::NONE)
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
uint8_t* Board::serialize()
{
    uint8_t* serial = new uint8_t[65];
    memset(serial, 0, 64);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j]) serial[i * 8 + j] = (1 << 7) |
                ((int)grid[i][j]->player << 6) | (int)grid[i][j]->type;
        }
    }
    serial[64] = (int)next;
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
                switch ((PieceType)(serial[i * 8 + j] & 0b111))
                {
                case PieceType::PAWN:
                    board->grid[i][j] = new Pawn(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PieceType::ROOK:
                    board->grid[i][j] = new Rook(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PieceType::KNIGHT:
                    board->grid[i][j] = new Knight(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PieceType::BISHOP:
                    board->grid[i][j] = new Bishop(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PieceType::QUEEN:
                    board->grid[i][j] = new Queen(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    break;
                case PieceType::KING:
                    board->grid[i][j] = new King(Point(i, j), 
                        (Player)((serial[i * 8 + j] & (1 << 6)) >> 6));
                    ((Player)((serial[i * 8 + j] & (1 << 6)) >> 6) == Player::WHITE 
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
#ifdef HAVE_TORCH
using namespace torch;
using namespace nn;
Tensor Board::encode()
{
    Tensor encoded = torch::empty({6, 8, 8});
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (grid[i][j]) encoded[(int)grid[i][j]->type][i][j] = 
                grid[i][j]->player == next ? 1 : -1;
        }
    }
    return encoded;
}
#endif
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