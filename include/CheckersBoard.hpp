#pragma once

#include "CheckersPiece.hpp"
#include "Constants.hpp"

#include <vector>

class CheckersPiece;

class CheckersBoard: public Board
{
    private:
        std::vector<std::vector<std::unique_ptr<CheckersPiece>>> m_board;
    public:
        explicit CheckersBoard(std::vector<std::shared_ptr<Player>> players);
        ~CheckersBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const CheckersBoard& board);

        void Init() override;
        void FillBoardWithEmptyPieces() override;
        void SetPieceOnBoard() override;
        void MovePiece(int x, int y, int newX, int newY) override;

        CheckersPiece* GetValueAt(int x, int y) const
        {
            if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
                throw std::out_of_range("x or y is out of range");

            return m_board[x][y].get();
        };
};