#ifndef _CHECKERSGAME
#define _CHECKERSGAME

#include "Game.hpp"
#include "Player.hpp"
#include "Board.hpp"

#include <memory>

class CheckersGame : public Game
{
    public:
        CheckersGame();
        ~CheckersGame() override;

        // Logic
        void run() override;
        void startGame(Board& board, std::vector<Player*>& players) override;
        void playTurn(Board& board, Player& player) override;
        // Rules

        // UI
};

#endif