#include "../include/Piece.hpp"

#include <vector>

Piece::Piece() {}

Piece::Piece(int x, int y/*, std::shared_ptr<Player> owner*/, char symbol)
    : m_x(x), m_y(y)
{
    //m_state.m_owner = std::move(owner);
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

int Piece::GetX() const
{
    return m_x;
}

int Piece::GetY() const
{
    return m_y;
}

/*Player& Piece::GetOwner() const
{
    return *m_state.m_owner;
}*/

char Piece::GetSymbol() const
{
    return m_state.m_symbol;
}