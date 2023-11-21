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
        bool isCordValid(int ligne,int col);
        bool isDestValid(int ligne1,int col1,int ligne2,int col2,
                                                Player& player,Board& board);
        bool canPieceBeEaten(int ligne1,int col1,int ligne2,int col2,Player& player,Board& board);
        // UI
};

#endif