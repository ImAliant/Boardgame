#include "../include/Piece.hpp"

#include <vector>

Piece::Piece() {}

Piece::Piece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol)
    : m_x(x), m_y(y), m_color(color), m_owner(std::move(owner)), m_symbol(symbol) {}

Piece::~Piece() {}

Piece& Piece::operator=(const Piece& piece)
{
    if (this != &piece)
    {
        m_x = piece.m_x;
        m_y = piece.m_y;
        m_color = piece.m_color;
        m_owner = std::make_shared<Player>(*piece.m_owner);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
    os << piece.getSymbol();
    return os;
}

// Checkers pour l'instant
void Piece::findPossibleMoves(const Board& board,GameType gameType)
{
    m_possibleMoves.clear();
    if (gameType == GameType::CHECKERS)
    {
        std::vector<std::pair<int, int>> directionsUp = {{-1, -1}, {-1, 1}};
        std::vector<std::pair<int, int>> directionsDown = {{1, -1}, {1, 1}};

        if (m_color == sf::Color::White)
        {
            for (const auto& [dx, dy] : directionsUp)
            {
                int x = m_x + dx;
                int y = m_y + dy;

                if (x >= 0 && x < board.getRows() && y >= 0 && y < board.getCols())
                {
                    if (board.getValueAt(x, y)->getColor() == sf::Color::Transparent)
                    {
                        m_possibleMoves.push_back(std::make_pair(x, y));
                    }
                }
            }
        }
        else if (m_color == sf::Color::Black)
        {
            for (const auto& [dx, dy] : directionsDown)
            {
                int x = m_x + dx;
                int y = m_y + dy;

                if (x >= 0 && x < board.getRows() && y >= 0 && y < board.getCols())
                {
                    if (board.getValueAt(x, y)->getColor() == sf::Color::Transparent)
                    {
                        m_possibleMoves.push_back(std::make_pair(x, y));
                    }
                }
            }
    
        }
    }else if (gameType == GameType::BUTIN)
    {
        // A yellow pice can move in all directions by jumping over now yellow pices
       
        if (m_color == sf::Color::Yellow)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int x = m_x + dx;
                    int y = m_y + dy;

                    if (x >= 0 && x < board.getRows() && y >= 0 && y < board.getCols())
                    {
                        Piece* neighborPiece = board.getValueAt(x, y);

                        // Check if the neighbor is not yellow
                        if (neighborPiece->getColor() != sf::Color::Yellow)
                        {
                            // Jump to the position beyond the neighbor
                            int jumpX = x + dx;
                            int jumpY = y + dy;

                            // Check if the jump position is within the bounds and is empty
                            if (jumpX >= 0 && jumpX < board.getRows() && jumpY >= 0 && jumpY < board.getCols() &&
                                board.getValueAt(jumpX, jumpY)->getColor() == sf::Color::Transparent)
                            {
                                m_possibleMoves.push_back(std::make_pair(jumpX, jumpY));
                            }
                        }
                    }
                }
            }
        }
    }

}


void Piece::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

std::vector<std::pair<int, int>> Piece::getPossibleMoves() const
{
    return m_possibleMoves;
}

std::pair<int, int> Piece::getPosition() const
{
    return std::make_pair(m_x, m_y);
}

Player& Piece::getOwner() const
{
    return *m_owner;
}

sf::Color Piece::getColor() const
{
    return m_color;
}

char Piece::getSymbol() const
{
    return m_symbol;
}