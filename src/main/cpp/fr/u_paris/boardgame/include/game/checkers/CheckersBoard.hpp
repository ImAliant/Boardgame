#pragma once

#include "../Board.hpp"

class CheckersBoard: public Board
{
    private:
        void FillBoard() override;
        void CreateBlackPiece(const int i, const int j);
        void CreateWhitePiece(const int i, const int j);

        void CreatePiece(const int i, const int j, const char symbol) override;
    public:
        explicit CheckersBoard();
        ~CheckersBoard() override = default;
};