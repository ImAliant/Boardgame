#pragma once

#include "../Board.hpp"

class BulltrickerBoard: public Board
{
    private:
        void FillBoard() override;

        void CreatePiece(const int i, const int j, const char symbol) override;
        void CreateKings();
        void CreateQueens();
        void CreateHorizontalPawns();
        void CreateVerticalPawns();
    public:
        explicit BulltrickerBoard();
        ~BulltrickerBoard() override = default;

        void SetHorizontal(const int i, const int j, const bool h) const;
};