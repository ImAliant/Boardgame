#pragma once

#include "../Game.hpp"

class Bulltricker: public Game
{
    public:
        Bulltricker();
        ~Bulltricker() override = default;

        void Init() override;
};