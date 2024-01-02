#pragma once

#include "../../Piece.hpp"




enum PieceType
{
    EMPTY,
    PAWN,
    QUEEN,
    KING
};

class BulltrickerPiece: public Piece
{
    public:
        BulltrickerPiece(coord_t coord, const std::shared_ptr<Player> owner,char color, bool king, bool queen);
        ~BulltrickerPiece() override = default;
        void CaptureMoves(const Board& board) override {
            // Implementation specific to BulltrickerPiece
        }
};