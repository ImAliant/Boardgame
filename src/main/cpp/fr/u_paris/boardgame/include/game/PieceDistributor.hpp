#pragma once

class PieceDistributor
{
    public:
        virtual void DistributePieces() = 0;
        virtual ~PieceDistributor() = default;
};