#pragma once

#include "CheckersPiece.hpp"
#include "Constants.hpp"

#include <vector>

class CheckersPiece;

class CheckersBoard: public Board
{
    private:
        std::vector<std::vector<std::unique_ptr<CheckersPiece>>> m_board;

        void CheckBounds(coord_t coord) const;
        std::unique_ptr<CheckersPiece> CreatePiece(coord_t coord, char color) const;
        std::unique_ptr<CheckersPiece> CreateTransparentPiece(coord_t coord) const;
        std::unique_ptr<CheckersPiece> CreateBlackPiece(coord_t coord) const;
        std::unique_ptr<CheckersPiece> CreateWhitePiece(coord_t coord) const;
    public:
        explicit CheckersBoard(std::vector<std::shared_ptr<Player>> players);
        ~CheckersBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const CheckersBoard& board);

        void Init() override;
        void FillBoard() override;
        void MovePiece(coord_t coord, coord_t newCoord) override;
        void RemovePiece(coord_t coord) override;

        bool EmptyCell(coord_t coord) const;
        bool IsOpponentPiece(coord_t srcCoord, coord_t dstCoord) const;

        CheckersPiece* GetValueAt(coord_t coord) const
        {
            const auto& [x, y] = coord;
            if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
                throw std::out_of_range("x or y is out of range");

            return m_board[x][y].get();
        };
};