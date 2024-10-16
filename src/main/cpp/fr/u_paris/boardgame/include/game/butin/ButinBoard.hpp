#pragma once

#include "../Board.hpp"

using to_fill_t = std::vector<std::pair<char, int>>;

class ButinBoard: public Board
{
    private:
        void FillBoard() override;
        void ShuffleSymbols(std::vector<char>& symbols) const;

        void CreatePiece(const int i, const int j, const char symbol) override;
    public:
        explicit ButinBoard();
        ~ButinBoard() override = default;
};