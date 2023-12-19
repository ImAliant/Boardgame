#include "../include/Piece.hpp"

#include <vector>

Piece::Piece() {}

Piece::Piece(coord_t coord, std::shared_ptr<Player> owner, char symbol)
    : m_x(coord.first), m_y(coord.second)
{
    m_state.m_owner = std::move(owner);
    m_state.m_symbol = symbol;
}

void Piece::SetPosition(coord_t coord)
{
    const auto& [x, y] = coord;
    m_x = x;
    m_y = y;
}

std::vector<coord_t> Piece::GetPossibleMoves() const
{
    return m_possibleMoves;
}

coord_t Piece::GetPosition() const
{
    return std::make_pair(m_x, m_y);
}

int Piece::GetX() const
{
    return m_x;
}

int Piece::GetY() const
{
    return m_y;
}

std::shared_ptr<Player> Piece::GetOwner() const
{
    return m_state.m_owner;
}

char Piece::GetSymbol() const
{
    return m_state.m_symbol;
}