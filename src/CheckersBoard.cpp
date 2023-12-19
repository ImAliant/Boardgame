#include "../include/CheckersBoard.hpp"

using namespace CheckersConstants;

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

    FillBoard();
}

void CheckersBoard::FillBoard()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (i < 4 && (i + j) % 2 != 0)
            {
                m_board[i][j] = CreatePiece(i, j, BLACK);
            }
            else if (i > 5 && (i + j) % 2 != 0)
            {
                m_board[i][j] = CreatePiece(i, j, WHITE);
            }
            else
                m_board[i][j] = CreatePiece(i, j, TRANSPARENT);
        }
    }
}

void CheckersBoard::MovePiece(int x, int y, int newX, int newY)
{
    CheckBounds(x, y);
    CheckBounds(newX, newY);

    // On recupere la piece a deplacer
    auto piece = std::move(m_board[x][y]);
    piece->SetPosition(newX, newY);

    m_board[newX][newY] = std::move(piece);
    m_board[x][y] = CreatePiece(x, y, TRANSPARENT);
}

void CheckersBoard::RemovePiece(int x, int y)
{
    CheckBounds(x, y);

    m_board[x][y] = CreatePiece(x, y, TRANSPARENT);
}

bool CheckersBoard::EmptyCell(int x, int y) const
{
    CheckBounds(x, y);

    return GetValueAt(x, y)->GetSymbol() == TRANSPARENT;
}

void CheckersBoard::CheckBounds(int x, int y) const
{
    if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
    {
        throw std::out_of_range("x or y is out of range");
    }
}

bool CheckersBoard::IsOpponentPiece(int sx, int sy, int dx, int dy) const
{
    CheckBounds(sx, sy);
    CheckBounds(dx, dy);

    if (GetValueAt(sx, sy)->GetSymbol() == GetValueAt(dx, dy)->GetSymbol())
        return false;
    if (GetValueAt(sx, sy)->GetSymbol() == TRANSPARENT || GetValueAt(dx, dy)->GetSymbol() == TRANSPARENT)
        return false;
    
    return true;
}

std::unique_ptr<CheckersPiece> CheckersBoard::CreatePiece(int x, int y, char color) const
{
    if (color == BLACK)
        return CreateBlackPiece(x, y);
    else if (color == WHITE)
        return CreateWhitePiece(x, y);
    else if (color == TRANSPARENT)
        return CreateTransparentPiece(x, y);
    else throw std::invalid_argument("Invalid color");
}
std::unique_ptr<CheckersPiece> CheckersBoard::CreateTransparentPiece(int x, int y) const
{
    return std::make_unique<CheckersPiece>(x, y, nullptr/*m_players[NONEID]*/, TRANSPARENT);
}
std::unique_ptr<CheckersPiece> CheckersBoard::CreateBlackPiece(int x, int y) const
{
    return std::make_unique<CheckersPiece>(x, y, m_players[PLAYER_TWOID], BLACK);
}
std::unique_ptr<CheckersPiece> CheckersBoard::CreateWhitePiece(int x, int y) const
{
    return std::make_unique<CheckersPiece>(x, y, m_players[PLAYER_ONEID], WHITE);
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