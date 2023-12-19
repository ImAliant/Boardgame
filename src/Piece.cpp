#include "../include/Piece.hpp"

#include <vector>

Piece::Piece() {}

Piece::Piece(coord_t coord, std::shared_ptr<Player> owner, char symbol)
    : m_coord(coord), m_state({0, std::move(owner), symbol})
{}

void Piece::SetPosition(coord_t coord)
{
    m_coord = coord;
}

std::vector<coord_t> Piece::GetPossibleMoves() const
{
    return m_possibleMoves;
}

coord_t Piece::GetPosition() const
{
    return m_coord;
}

int Piece::GetX() const
{
    return m_coord.first;
}

int Piece::GetY() const
{
    return m_coord.second;
}

std::shared_ptr<Player> Piece::GetOwner() const
{
    return m_state.m_owner;
}

char Piece::GetSymbol() const
{
    return m_state.m_symbol;
}