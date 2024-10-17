#pragma once

#include "../Game.hpp"
#include "../PieceDistributor.hpp"

class Checkers: public Game, public PieceDistributor
{
    public:
        Checkers();
        ~Checkers() override = default;

        void Init() override;
        void InitPlayers() override;

        void DistributePieces() override;
};