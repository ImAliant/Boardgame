#include "Piece.hpp"

Piece::Piece(const coord_t c, const char s): coord{c}, symbol{s} {}

Piece::~Piece() {}

void Piece::SetCoord(const coord_t c)
{
    coord = c;
}

coord_t Piece::GetCoord() const
{
    return coord;
}

char Piece::GetSymbol() const
{
    return symbol;
}
