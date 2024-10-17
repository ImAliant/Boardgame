#pragma once

#include "../Game.hpp"

class Butin: public Game
{
    public:
        Butin();
        ~Butin() override = default;

        void Init() override;

        void Start() override;
};