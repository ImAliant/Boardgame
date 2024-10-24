#pragma once

#include "../Board.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::Bulltricker;

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

        std::shared_ptr<BulltrickerPiece> GetSpecificKing(const Color c) const;

        void SetOrientation(const coord_t coord, const Orientation o) const;
        void SetColor(const coord_t coord, const Color c) const;
        void SetKing(const coord_t coord) const;
        void SetQueen(const coord_t coord) const;
};