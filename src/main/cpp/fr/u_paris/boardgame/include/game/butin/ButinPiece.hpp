#pragma once

#include "../Piece.hpp"

class ButinPiece: public Piece
{
    public:
        explicit ButinPiece(const coord_t c, const char s);
        ~ButinPiece() override = default;
};