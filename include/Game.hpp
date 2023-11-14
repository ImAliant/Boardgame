#ifndef _GAME
#define _GAME

#include <memory>
#include <vector>

#include "Player.hpp"
#include "Board.hpp"

class Game
{
    public:
        virtual ~Game() = default;

        virtual void run() = 0;
        virtual void startGame(Board& board, std::vector<Player>& players) = 0;
        virtual void playTurn(Board& board, Player& player) = 0;
};

#endif