#pragma once

#include "../Piece.hpp"

class ButinPiece: public Piece
{
    private: 
        void FindSimpleMoves(std::shared_ptr<Board> board) override;
        void FindJumpMoves(std::shared_ptr<Board> board) override;
    public:
        explicit ButinPiece(const coord_t c, const char s);
        ~ButinPiece() override = default;
};