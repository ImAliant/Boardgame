#pragma once

#include "../Piece.hpp"

class CheckersPiece: public Piece
{
    public:
        explicit CheckersPiece(const coord_t c, const char s);
        ~CheckersPiece() override = default;

        void SetPossibleMoves(std::shared_ptr<Board> board) override;
};