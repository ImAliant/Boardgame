#include "../include/Piece.hpp"

#include <vector>

Piece::Piece() {}

Piece::Piece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol)
    : m_x(x), m_y(y)
{
    m_state.type = 0;
    m_state.m_color = color;
    m_state.m_owner = std::move(owner);
    m_state.m_symbol = symbol;
}

void Piece::SetPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

std::vector<std::pair<int, int>> Piece::GetPossibleMoves() const
{
    return m_possibleMoves;
}

std::pair<int, int> Piece::GetPosition() const
{
    return std::make_pair(m_x, m_y);
}

Player& Piece::GetOwner() const
{
    return *m_state.m_owner;
}

sf::Color Piece::GetColor() const
{
    return m_state.m_color;
}

char Piece::GetSymbol() const
{
    return m_state.m_symbol;
}