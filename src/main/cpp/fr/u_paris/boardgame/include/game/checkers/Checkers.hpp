#pragma once

#include "../Game.hpp"

class Checkers: public Game
{
    public:
        Checkers();
        ~Checkers() override = default;

        void Init() override;
};