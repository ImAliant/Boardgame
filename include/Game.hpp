#ifndef _GAME
#define _GAME

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
        virtual ~Game() = default;

        virtual void run() = 0;
        virtual void init() = 0;
        virtual void initPlayers() = 0;
};

#endif