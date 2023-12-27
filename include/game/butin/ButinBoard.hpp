#pragma once

#include "ButinPiece.hpp"
#include "../../Constants.hpp"
#include "../../Board.hpp"
#include <vector>

class ButinPiece;

class ButinBoard: public Board
{
    private:
        std::vector<std::vector<std::unique_ptr<ButinPiece>>> m_board;
     
        void CheckBounds(coord_t coord) const;
        std::unique_ptr<ButinPiece> CreatePiece(coord_t coord, char color) const;
        std::unique_ptr<ButinPiece> CreateBlackPiece(coord_t coord) const;
        std::unique_ptr<ButinPiece> CreateRedPiece(coord_t coord) const;
        std::unique_ptr<ButinPiece> CreateYellowPiece(coord_t coord) const;
    public:
        explicit ButinBoard(std::vector<std::shared_ptr<Player>> players);
        
        ~ButinBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const ButinBoard& board);

        void Init() override;
        void FillBoard() override;
        void MovePiece(coord_t coord, coord_t newCoord) override;
        void RemovePiece(coord_t coord) override;

        void RemoveJumpedPiece(coord_t start, coord_t end);
        
        bool EmptyCell(coord_t coord) const;
        bool IsJumpablePiece(coord_t srcCoord, coord_t dstCoord) const;

        ButinPiece* GetValueAt(coord_t coord) const
        {
            const auto& [x, y] = coord;
            if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
                throw std::out_of_range("x or y is out of range");

            return m_board[x][y].get();
        };
};