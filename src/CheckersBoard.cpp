#include "../include/CheckersBoard.hpp"

CheckersBoard::CheckersBoard(std::vector<std::shared_ptr<Player>> players)
: Board(std::move(players))
{
    m_rows = CHECKERSROWS;
    m_cols = CHECKERSCOLS;

    CheckersBoard::Init();
}

void CheckersBoard::Init()
{
    m_board.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        m_board[i].resize(m_cols);
    }

    FillBoardWithEmptyPieces();
    SetPieceOnBoard();
}

void CheckersBoard::FillBoardWithEmptyPieces()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            m_board[i][j] = std::make_unique<CheckersPiece>(i, j, m_players[2], sf::Color::Transparent, ' ');
        }
    }
}

void CheckersBoard::SetPieceOnBoard()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (i < 4 && (i + j) % 2 != 0)
            {
                m_board[i][j] = std::make_unique<CheckersPiece>(i, j, m_players[0], sf::Color::Black, 'X');
            }
            else if (i > 5 && (i + j) % 2 != 0)
            {
                m_board[i][j] = std::make_unique<CheckersPiece>(i, j, m_players[1], sf::Color::White, 'O');
            }
            else
                continue;
        }
    }
}

void CheckersBoard::MovePiece(int x, int y, int newX, int newY)
{
    if (x < 0 || x >= m_rows || y < 0 || y >= m_cols || newX < 0 || newX >= m_rows || newY < 0 || newY >= m_cols)
    {
        throw std::out_of_range("x or y is out of range");
    }

    // On recupere la piece a deplacer
    auto piece = std::move(m_board[x][y]);
    piece->SetPosition(newX, newY);

    m_board[newX][newY] = std::move(piece);
    m_board[x][y] = std::make_unique<CheckersPiece>(x, y, m_players[2], sf::Color::Transparent, ' ');
}

std::ostream &operator<<(std::ostream &os, const CheckersBoard &board)
{
    for (int i = 0; i < board.m_rows; i++)
    {
        for (int j = 0; j < board.m_cols; j++)
        {
            os << *board.m_board[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}