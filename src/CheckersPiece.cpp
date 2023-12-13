#include "../include/CheckersPiece.hpp"

CheckersPiece::CheckersPiece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol)
    : Piece(x, y, std::move(owner), color, symbol)
{
    m_state.type = PieceType::PAWN;
}

CheckersPiece::~CheckersPiece() {}

void CheckersPiece::FindPossibleMoves(const Board& board)
{
    const auto& checkersBoard = dynamic_cast<const CheckersBoard&>(board);

    m_possibleMoves.clear();

    std::vector<std::pair<int, int>> directionsUp = {{-1, -1}, {-1, 1}};
    std::vector<std::pair<int, int>> directionsDown = {{1, -1}, {1, 1}};

    if (m_state.m_color == sf::Color::White)
    {
        for (const auto& [dx, dy] : directionsUp)
        {
            int x = m_x + dx;
            int y = m_y + dy;

            if (x >= 0 && x < board.GetRows() && y >= 0 && y < board.GetCols())
            {
                if (checkersBoard.GetValueAt(x, y)->GetColor() == sf::Color::Transparent)
                {
                    m_possibleMoves.push_back(std::make_pair(x, y));
                }
            }
        }
    }
    else if (m_state.m_color == sf::Color::Black)
    {
        for (const auto& [dx, dy] : directionsDown)
        {
            int x = m_x + dx;
            int y = m_y + dy;

            if (x >= 0 && x < board.GetRows() && y >= 0 && y < board.GetCols())
            {
                if (checkersBoard.GetValueAt(x, y)->GetColor() == sf::Color::Transparent)
                {
                    m_possibleMoves.push_back(std::make_pair(x, y));
                }
            }
        }
    }
}

void CheckersPiece::Promote()
{
    m_state.type = PieceType::QUEEN;
    m_state.m_symbol = 'Q';
}

bool CheckersPiece::IsPromoted() const
{
    return m_state.type == PieceType::QUEEN;
}

std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}