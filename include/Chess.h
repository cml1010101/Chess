#ifndef CHESSUTILS_H
#define CHESSUTILS_H
#include <vector>
#include <map>
#include <ostream>
namespace chess
{
    enum Player
    {
        PLAYER_WHITE = 0,
        PLAYER_BLACK = 1
    };
    inline Player other(Player player)
    {
        return (player == PLAYER_WHITE) ? PLAYER_BLACK : PLAYER_WHITE;
    }
    inline int direction(Player player)
    {
        return (player == PLAYER_WHITE) ? 1 : -1;
    }
    inline int starting_row(Player player)
    {
        return (player == PLAYER_WHITE) ? 0 : 7;
    }
    enum PieceType
    {
        PIECE_PAWN,
        PIECE_ROOK,
        PIECE_KNIGHT,
        PIECE_BISHOP,
        PIECE_QUEEN,
        PIECE_KING
    };
    class Point
    {
    public:
        int row, col;
        inline Point()
        {
            row = -1;
            col = -1;
        }
        Point(int row, int col)
        {
            this->row = row;
            this->col = col;
        }
        Point(std::initializer_list<int> meta)
        {
            this->row = meta.begin()[0];
            this->col = meta.begin()[1];
        }
        inline friend Point operator+(Point a, Point b)
        {
            return {a.row + b.row, a.col + b.col};
        }
        inline friend Point operator-(Point a, Point b)
        {
            return {a.row - b.row, a.col - b.col};
        }
        inline friend Point operator*(Point a, int b)
        {
            return {a.row * b, a.col * b};
        }
        inline friend Point operator/(Point a, int b)
        {
            return {a.row / b, a.col / b};
        }
        inline friend Point operator+(Point a, std::initializer_list<int> meta)
        {
            return {a.row + meta.begin()[0], a.col + meta.begin()[1]};
        }
        inline friend Point operator-(Point a, std::initializer_list<int> meta)
        {
            return {a.row - meta.begin()[0], a.col - meta.begin()[1]};
        }
        inline operator bool()
        {
            return (row >= 0 && row < 8) && (col >= 0 && col < 8);
        }
    };
    class Move
    {
    public:
        Point src, dest;
        Move() = default;
        inline Move(Point src, Point dest)
        {
            this->src = src;
            this->dest = dest;
        }
        inline static Move* resign()
        {
            return new Move({-1, -1}, {-1, -1});
        }
    };
    class Board;
    class Piece
    {
    public:
        PieceType type;
        Point loc;
        double value;
        Player player;
        Piece() = default;
        inline Piece(Point loc, Player player, PieceType type, double value)
        {
            this->loc = loc;
            this->player = player;
            this->type = type;
            this->value = value;
        }
        virtual bool canMove(Board* board, Move* move) = 0;
        virtual std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true) = 0;
        virtual Piece* clone() = 0;
    };
    class Pawn : public Piece
    {
    public:
        inline Pawn(Point loc, Player player) : Piece(loc, player, PIECE_PAWN, 1)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
    class Rook : public Piece
    {
    public:
        inline Rook(Point loc, Player player) : Piece(loc, player, PIECE_ROOK, 5)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
    class Knight : public Piece
    {
    public:
        inline Knight(Point loc, Player player) : Piece(loc, player, PIECE_KNIGHT, 3)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
    class Bishop : public Piece
    {
    public:
        inline Bishop(Point loc, Player player) : Piece(loc, player, PIECE_BISHOP, 3)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
    class Queen : public Piece
    {
    public:
        inline Queen(Point loc, Player player) : Piece(loc, player, PIECE_QUEEN, 9)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
    class King : public Piece
    {
    public:
        inline King(Point loc, Player player) : Piece(loc, player, PIECE_KING, 0)
        {
        }
        bool canMove(Board* board, Move* move);
        std::vector<Move*> getPossibleMoves(Board* board, bool checkForCheck = true);
        Piece* clone();
    };
    class Board
    {
    public:
        Piece* grid[8][8];
        Player next;
        Point kingWhite, kingBlack;
        int winner;
        Board();
        bool canMove(Move* move, bool checkForCheck = true);
        void playMove(Move* move);
        std::vector<Piece*> getPieces(Player player);
        std::vector<Move*> getPossibleMoves(bool checkForCheck = true);
        bool inCheck();
        Board* clone();
    };
    class Bot
    {
    public:
        Bot() = default;
        virtual Move* findMove(Board* board) = 0;
    };
    class Game
    {
    public:
        std::vector<Board*> boards;
        std::vector<Move*> moves;
        std::map<Player, Bot*> bots;
        Game() = default;
        Game(Bot* whiteBot, Bot* blackBot);
        Board* getCurrentBoard();
        void playMove(Move* move);
        void step();
    };
}
std::ostream& operator<<(std::ostream& out, chess::Board* board);
#endif