#pragma once

#include "../../Piece.hpp"

enum BT_PieceType
{
    BT_EMPTY,
    BT_PAWN,
    BT_QUEEN,
    BT_KING
};

class BulltrickerPiece: public Piece
{
    private:
        bool m_isHorizontal;

        void SimpleMoves(const Board& board);
        void CaptureMoves(const Board& board) override;
    public:
        BulltrickerPiece(const coord_t coord, const std::shared_ptr<Player> owner, 
                         const char symbol, const int type, 
                         const bool m_isHorizontal);
        ~BulltrickerPiece() override;

        void FindPossibleMoves(const Board& board) override;

        void Promote();
        bool IsPromoted() const;
        bool IsHorizontal() const;
};