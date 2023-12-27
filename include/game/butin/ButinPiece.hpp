#pragma once

#include "../../Piece.hpp"
#include "ButinBoard.hpp"
#include "../../Constants.hpp"

class ButinBoard;

enum Butin_PieceType
{
    BUTIN_EMPTY,
    YELLOW,
    RED,
    BLACK
};

class ButinPiece: public Piece
{
    private:
        bool m_canBeCaptured = false;

        std::vector<direction_t> m_possibleCaptures;

        bool IsWithinBoard(const ButinBoard& board, coord_t coord) const;
        bool IsEmptyCell(const ButinBoard& board, coord_t coord) const;
    public:
        ButinPiece() = default;
        ButinPiece(coord_t coord, char symbol);
        ~ButinPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const ButinPiece& piece);

        void FindPossibleMoves(const Board& board) override;

        bool HasPieceToJump(const ButinBoard& board, coord_t current, coord_t next) const;
        
        std::vector<direction_t> GetPossibleCaptures() const;
};
