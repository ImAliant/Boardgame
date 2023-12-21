#pragma once

#include "ButinPiece.hpp"
#include "Constants.hpp"
#include "Board.hpp"
#include <vector>

class ButinPiece;

class ButinBoard: public Board
{
    private:
        std::vector<std::vector<std::unique_ptr<ButinPiece>>> m_board;

        void CheckBounds(int x, int y) const;
        std::unique_ptr<ButinPiece> CreatePiece(int x, int y, char color) const;
        std::unique_ptr<ButinPiece> CreateTransparentPiece(int x, int y) const;
        std::unique_ptr<ButinPiece> CreateBlackPiece(int x, int y) const;
        std::unique_ptr<ButinPiece> CreateRedPiece(int x, int y) const;
        std::unique_ptr<ButinPiece> CreateYellowPiece(int x, int y) const;
    public:
        explicit ButinBoard(std::vector<std::shared_ptr<Player>> players);
        ~ButinBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const ButinBoard& board);

        void Init() override;
        void FillBoard() override;
        void MovePiece(int x, int y, int newX, int newY) override;
        void RemovePiece(int x, int y) override;

        bool EmptyCell(int x, int y) const;
        bool IsJumpablePiece(int sx, int sy, int dx, int dy) const;

        ButinPiece* GetValueAt(int x, int y) const
        {
            if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
                throw std::out_of_range("x or y is out of range");

            return m_board[x][y].get();
        };
};