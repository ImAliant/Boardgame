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

        void Start() override;

        void DistributePieces() override;
};