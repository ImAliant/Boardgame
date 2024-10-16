#include "game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(
    const coord_t c, 
    const char s): Piece(c, s) {}

bool BulltrickerPiece::IsHorizontal() const
{
    return is_horizontal;
}

void BulltrickerPiece::SetHorizontal(const bool h)
{
    is_horizontal = h;
}