#pragma once

#include "../Game.hpp"
#include "../PieceDistributor.hpp"

class Bulltricker: public Game, public PieceDistributor
{
    public:
        Bulltricker();
        ~Bulltricker() override = default;

        void Init() override;
        void InitPlayers() override;

        void Start() override;

        void DistributePieces() override;
};