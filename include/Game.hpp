#ifndef _GAME
#define _GAME

#include "Rules.hpp"

#include <memory>

enum class GameType
{
    Checkers,
    Jeu2,
    Jeu3
};

// Classe abstraite
class Game
{
    public:
        virtual void run() = 0;
        virtual ~Game() = default;
    private:
        // Une partie est composée de règles
        std::unique_ptr<Rules> rules;
};

#endif