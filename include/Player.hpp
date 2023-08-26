#ifndef PLAYER_HPP
#define PLAYER_HPP
namespace chess
{
    enum struct Player : int
    {
        WHITE = 0,
        BLACK = 1
    };
    inline Player other(Player player)
    {
        return (player == Player::WHITE) ? Player::BLACK : Player::WHITE;
    }
    inline int direction(Player player)
    {
        return (player == Player::WHITE) ? 1 : -1;
    }
    inline int starting_row(Player player)
    {
        return (player == Player::WHITE) ? 0 : 7;
    }
}
#endif