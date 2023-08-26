#ifndef NEURALBOT_HPP
#define NEURALBOT_HPP
#include <Bot.hpp>
namespace chess
{
#ifdef HAVE_TORCH
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
#endif
}
#endif