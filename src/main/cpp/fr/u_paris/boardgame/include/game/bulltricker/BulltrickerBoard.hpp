#pragma once

#include "../Board.hpp"

class BulltrickerBoard: public Board
{
    private:
        void FillBoard() override;

        void CreatePiece(const int i, const int j, const char symbol) override;
    public:
        explicit BulltrickerBoard();
        ~BulltrickerBoard() override = default;

        void SetHorizontal(const int i, const int j, const bool h) const;
};