#include <Move.hpp>
#include <PieceType.hpp>
#include <Board.hpp>
using namespace chess;
using namespace std;
using namespace boost;
Move* Move::parse(smatch match, Board* board)
{
    PieceType type = PieceType::PAWN;
    string typeStr = string(match[1].begin(), match[1].end());
    if (typeStr == "R")
    {
        type = PieceType::ROOK;
    }
    else if (typeStr == "N")
    {
        type = PieceType::KNIGHT;
    }
    else if (typeStr == "B")
    {
        type = PieceType::BISHOP;
    }
    else if (typeStr == "Q")
    {
        type = PieceType::QUEEN;
    }
    else if (typeStr == "K")
    {
        type = PieceType::KING;
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
string Move::toSAN(Board* board)
{
    if (isResign)
    {
        if (board->next == Player::BLACK) return "1-0";
        return "0-1";
    }
    else if (isDraw)
    {
        return "1/2-1/2";
    }
    string typeStr = "";
    PieceType type = board->grid[src.row][src.col]->type;
    if (type == PieceType::ROOK)
    {
        typeStr = "R";
    }
    if (type == PieceType::KNIGHT)
    {
        typeStr = "N";
    }
    if (type == PieceType::BISHOP)
    {
        typeStr = "B";
    }
    if (type == PieceType::QUEEN)
    {
        typeStr = "Q";
    }
    if (type == PieceType::KING)
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
#ifdef HAVE_TORCH
torch::Tensor Move::encode()
{
    auto tensor = torch::zeros({128});
    tensor[src.row * 8 + src.col] = 1;
    tensor[dest.row * 8 + dest.col] = 1;
    return tensor;
}
Move* Move::decode(at::Tensor tensor)
{
    int srcPos = argmax(tensor.slice(0, 0, 64)).item().toInt();
    int destPos = argmax(tensor.slice(0, 64, 128)).item().toInt();
    return new Move(Point(srcPos / 8, srcPos % 8), Point(destPos / 8, destPos % 8));
}
#endif