#pragma once

#include "../Piece.hpp"

class BulltrickerPiece: public Piece
{
    private:
        bool is_horizontal = false;
    public:
        explicit BulltrickerPiece(const coord_t c, const char s);
        ~BulltrickerPiece() override = default;

        bool IsHorizontal() const;

        void SetHorizontal(const bool h);
};