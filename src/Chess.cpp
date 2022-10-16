#include "../include/Chess.h"
#include <math.h>
#include <algorithm>
#include <iostream>
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
    grid[0][3] = new King(Point(0, 3), PLAYER_WHITE);
    grid[0][4] = new Queen(Point(0, 4), PLAYER_WHITE);
    grid[0][5] = new Bishop(Point(0, 5), PLAYER_WHITE);
    grid[0][6] = new Knight(Point(0, 6), PLAYER_WHITE);
    grid[0][7] = new Rook(Point(0, 7), PLAYER_WHITE);
    grid[7][0] = new Rook(Point(7, 0), PLAYER_BLACK);
    grid[7][1] = new Knight(Point(7, 1), PLAYER_BLACK);
    grid[7][2] = new Bishop(Point(7, 2), PLAYER_BLACK);
    grid[7][3] = new King(Point(7, 3), PLAYER_BLACK);
    grid[7][4] = new Queen(Point(7, 4), PLAYER_BLACK);
    grid[7][5] = new Bishop(Point(7, 5), PLAYER_BLACK);
    grid[7][6] = new Knight(Point(7, 6), PLAYER_BLACK);
    grid[7][7] = new Rook(Point(7, 7), PLAYER_BLACK);
    for (size_t i = 0; i < 8; i++)
    {
        grid[1][i] = new Pawn(Point(1, i), PLAYER_WHITE);
        grid[6][i] = new Pawn(Point(6, i), PLAYER_BLACK);
    }
    next = PLAYER_WHITE;
    kingWhite = Point(0, 3);
    kingBlack = Point(7, 3);
    winner = -1;
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
    if (!(move->src) && !(move->dest))
    {
        winner = next == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE;
        return;
    }
    grid[move->src.row][move->src.col]->loc = move->dest;
    grid[move->dest.row][move->dest.col] = grid[move->src.row][move->src.col];
    grid[move->src.row][move->src.col] = NULL;
    if (grid[move->dest.row][move->dest.col]->type == PIECE_KING)
    {
        Point& king = (next == PLAYER_WHITE) ? kingWhite : kingBlack;
        king = move->dest;
    }
    next = next == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE;
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
    playMove(bots[getCurrentBoard()->next]->findMove(getCurrentBoard()));
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
    return getPieces(PLAYER_WHITE).size() == 1 && getPieces(PLAYER_BLACK).size() == 1;
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
        return winner == next ? 0x1000 : -0x1000;
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
    cout << "Found move with score of " << idealScore << endl;
    return idealMoves[rand() % idealMoves.size()];
}