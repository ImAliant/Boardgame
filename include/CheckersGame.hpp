#ifndef _CHECKERSGAME
#define _CHECKERSGAME

#include "Game.hpp"
#include "CheckersRules.hpp"

#include <memory>

class CheckersGame : public Game
{
    public:
        void run() override;
        ~CheckersGame() override;
    private:
        // Une partie est composée de règles
        std::unique_ptr<CheckersRules> rules;
};

#endif