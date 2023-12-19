#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Piece.hpp"
#include "Types.hpp"

class Board
{
    protected:
        int m_rows = -1;
        int m_cols = -1;

        std::vector<std::shared_ptr<Player>> m_players;
    public:
        explicit Board(std::vector<std::shared_ptr<Player>> players) : m_players(std::move(players)) {}
        virtual ~Board() = default;

        virtual void Init() = 0;
        virtual void FillBoard() = 0;
        virtual void MovePiece(coord_t coord, coord_t newCoord) = 0;
        virtual void RemovePiece(coord_t coord) = 0;

        int GetRows() const { return m_rows; };
        int GetCols() const { return m_cols; };
};