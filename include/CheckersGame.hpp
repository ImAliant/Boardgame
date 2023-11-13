#ifndef _CHECKERSGAME
#define _CHECKERSGAME

#include "Game.hpp"
#include "Player.hpp"

#include <memory>
#include <vector>

class CheckersGame : public Game
{
    public:
        CheckersGame();
        ~CheckersGame() override;

        void run() override;
        void init() override;
        void initPlayers() override;
    private:
        std::vector<Player> players;
};

#endif