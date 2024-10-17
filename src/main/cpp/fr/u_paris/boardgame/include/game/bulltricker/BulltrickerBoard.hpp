#pragma once

#include "../Board.hpp"

class BulltrickerBoard: public Board
{
    private:
        void FillBoard() override;

        void CreatePiece(const coord_t coord, const char symbol) override;
        void CreateKings();
        void CreateQueens();
        void CreateHorizontalPawns();
        void CreateVerticalPawns();
    public:
        explicit BulltrickerBoard();
        ~BulltrickerBoard() override = default;

        void SetHorizontal(const coord_t coord, const bool h) const;
        void SetBlack(const coord_t coord, const bool b) const;
};