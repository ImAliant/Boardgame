#pragma once

#include "../Board.hpp"

using to_fill_t = std::vector<std::pair<char, int>>;

class ButinBoard: public Board
{
    private:
        void FillBoard() override;
        void ShuffleSymbols(std::vector<char>& symbols) const;

        void CreatePiece(const coord_t coord, const char symbol) override;
        void CreatePieces(const std::vector<char>& symbols);
        void GenerateSymbols(std::vector<char>& symbols);
    public:
        explicit ButinBoard();
        ~ButinBoard() override = default;
};