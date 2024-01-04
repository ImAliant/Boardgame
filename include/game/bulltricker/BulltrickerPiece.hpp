#pragma once

#include "../../Piece.hpp"




enum BullT_PieceType
{
    BT_EMPTY,
    BT_PAWN,
    BT_QUEEN,
    KING
};

class BulltrickerPiece: public Piece
{   
    private:
        bool m_isHorizontal;
    public:
        BulltrickerPiece(coord_t coord, const std::shared_ptr<Player> owner,char color, bool king, bool queen,bool isHorizontal);
        ~BulltrickerPiece() override = default;

        friend std::ostream& operator<<(std::ostream& os, const BulltrickerPiece& piece);

        void CaptureMoves(const Board& board) override {
            // Implementation specific to BulltrickerPiece
        }
        BullT_PieceType GetType() const;

        bool IsHorizontal() const;



        void Promote();
        bool IsPromoted() const;
};