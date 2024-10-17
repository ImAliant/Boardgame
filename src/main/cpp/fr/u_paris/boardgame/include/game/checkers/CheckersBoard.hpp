#pragma once

#include "../Board.hpp"

class CheckersBoard: public Board
{
    private:
        void FillBoard() override;
        void CreateBlackPiece(const coord_t coord);
        void CreateWhitePiece(const coord_t coord);

        void CreatePiece(const coord_t coord, const char symbol) override;
    public:
        explicit CheckersBoard();
        ~CheckersBoard() override = default;
};