#pragma once

#include "Game.hpp"

#include <memory>

class GameFactory 
{
    public:
        static std::shared_ptr<Game> CreateGame(const int type);
};