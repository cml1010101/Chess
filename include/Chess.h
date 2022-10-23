#ifndef CHESS_H
#define CHESS_H
#include <vector>
#include <map>
#include <ostream>
#include <torch/torch.h>
#include <boost/regex.hpp>
namespace chess
{
    class Board;
    enum Player
    {
        PLAYER_WHITE = 0,
        PLAYER_BLACK = 1
    };
    enum Winner
    {
        WINNER_WHITE = 0,
        WINNER_BLACK = 1,
        WINNER_DRAW = 2,
        WINNER_NONE = -1
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
        inline friend bool operator==(Point a, Point b)
        {
            return a.row == b.row && a.col == b.col;
        }
        inline static Point parse(std::string str)
        {
            return {str[1] - '1', str[0] >= 'a' ? str[0] - 'a' : str[0] - 'A'};
        }
        inline operator std::string()
        {
            char* buffer = new char[3];
            buffer[0] = col + 'a';
            buffer[1] = row + '1';
            buffer[2] = 0;
            return std::string(buffer);
        }
    };
    class Move
    {
    public:
        Point src, dest;
        bool isResign, isDraw;
        Move() = default;
        inline Move(Point src, Point dest, bool isResign = false, bool isDraw = false)
        {
            this->src = src;
            this->dest = dest;
            this->isResign = isResign;
            this->isDraw = isDraw;
        }
        inline static Move* resign()
        {
            return new Move({-1, -1}, {-1, -1}, true);
        }
        inline static Move* draw()
        {
            return new Move({-1, -1}, {-1, -1}, false, true);
        }
        static Move* parse(boost::smatch match, Board*);
        std::string toSAN(Board* board);
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
        torch::Tensor encode();
    };
    class Game;
    class Bot
    {
    public:
        Bot() = default;
        virtual Move* findMove(Board* board) = 0;
        virtual void handlePrint(Board* board)
        {
        }
        virtual void handleWinner(Winner winner)
        {
        }
        virtual void setPlayer(Player player)
        {
        }
        virtual void setGameReference(Game* gameReference)
        {
        }
        virtual void handleMove(Move* move, Board* board)
        {
        }
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
        std::string toPGN();
    };
    class MinimaxBot : public Bot
    {
    private:
        int maxDepth;
    public:
        MinimaxBot(int maxDepth);
        Move* findMove(Board* board);
    };
    class NeuralBot : public Bot
    {
    private:
        torch::nn::Sequential model;
    public:
        NeuralBot();
        Move* findMove(Board* board);
        ~NeuralBot();
        static void trainGames(std::vector<Game> games);
    };
}
std::ostream& operator<<(std::ostream& out, chess::Board board);
std::istream& operator>>(std::istream& in, chess::Game& game);
std::ostream& operator<<(std::ostream& out, chess::Game game);
#endif