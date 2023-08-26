#include <NeuralBot.hpp>
#include <Game.hpp>
#include <filesystem>
#ifdef HAVE_TORCH
using namespace chess;
using namespace std;
using namespace torch;
using namespace nn;
NeuralBot::NeuralBot()
{
    if (filesystem::exists("/usr/share/libchess/neuralbot.dat"))
    {
        load(model, "/usr/share/libchess/neuralbot.dat");
    }
    else
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
NeuralBot::~NeuralBot()
{
    save(model, "/usr/share/libchess/neuralbot.dat");
}
void NeuralBot::trainGames(std::vector<Game> games)
{
    torch::nn::Sequential model;
    if (filesystem::exists("/usr/share/neuralbot.dat"))
    {
        load(model, "/usr/share/neuralbot.dat");
    }
    else
    {
        model = Sequential(
            Conv2d(Conv2dOptions(6, 24, 3)),
            Flatten(FlattenOptions().start_dim(0).end_dim(-1)),
            Linear(LinearOptions(864, 864)),
            Sigmoid(),
            Linear(LinearOptions(864, 128)),
            Sigmoid()
        );
    }
    torch::optim::SGD sgd(model->parameters(), torch::optim::SGDOptions(5e-2));
    long numMoves = 0;
    for (auto game : games)
    {
        numMoves += game.moves.size();
    }
    Tensor xTrain = torch::empty({numMoves, 6, 8, 8});
    Tensor yTrain = torch::empty({numMoves, 128});
    size_t k = 0;
    for (auto game : games)
    {
        double outputValue = 0;
        if ((int)game.getCurrentBoard()->winner == (int)Player::WHITE)
            outputValue = 1;
        else if ((int)game.getCurrentBoard()->winner == (int)Player::BLACK)
            outputValue = -1;
        for (size_t i = 0; i < game.moves.size(); i++)
        {
            torch::Tensor t = game.boards[i]->encode();
            torch::Tensor t2 = game.moves[i]->encode();
            xTrain[k] = t;
            yTrain[k++] = t2;
        }
    }
    torch::optim::Adam adam(model->parameters(), torch::optim::AdamOptions(5e-4));
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < numMoves / 50; j++)
        {
            adam.zero_grad();
            for (size_t k = 0; k < 50; k++)
            {
                Tensor output = model->forward(xTrain[j * 50 + k]);
                Tensor tensor = torch::cross_entropy_loss(output, yTrain[j * 50 + k]);
                tensor.backward();
            }
            adam.step();
        }
    }
    save(model, "/usr/share/neuralbot.dat");
}
#endif