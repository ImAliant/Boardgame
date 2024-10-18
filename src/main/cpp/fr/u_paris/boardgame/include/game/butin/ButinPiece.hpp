#pragma once

#include "../Piece.hpp"

class ButinPiece: public Piece
{
    private: 
        void FindMoves(std::shared_ptr<Board> board) override;
    public:
        explicit ButinPiece(const coord_t c, const char s);
        ~ButinPiece() override = default;
};