#include "game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

bool BulltrickerPiece::IsHorizontal() const
{
    return is_horizontal;
}

bool BulltrickerPiece::IsBlack() const
{
    return is_black;
}

void BulltrickerPiece::SetHorizontal(const bool h)
{
    is_horizontal = h;
}

void BulltrickerPiece::SetBlack(const bool b)
{
    is_black = b;
}