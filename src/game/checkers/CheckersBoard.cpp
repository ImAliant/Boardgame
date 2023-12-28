#include "../../../include/game/checkers/CheckersBoard.hpp"

using namespace GameConstants::CheckersConstants;

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
            const auto& coord = std::make_pair(i, j);
            if (i < 4 && (i + j) % 2 != 0)
            {
                m_board[i][j] = CreatePiece(coord, BLACK);
            }
            else if (i > 5 && (i + j) % 2 != 0)
            {
                m_board[i][j] = CreatePiece(coord, WHITE);
            }
        }
    }
}

void CheckersBoard::MovePiece(coord_t coord, coord_t newCoord)
{
    CheckBounds(coord);
    CheckBounds(newCoord);

    // On recupere la piece a deplacer
    const auto& [x, y] = coord;
    auto piece = std::move(m_board[x][y]);
    piece->SetPosition(newCoord);

    const auto& [newX, newY] = newCoord;
    m_board[newX][newY] = std::move(piece);
    m_board[x][y] = nullptr;
}

void CheckersBoard::RemovePiece(coord_t coord)
{
    CheckBounds(coord);

    const auto& [x, y] = coord;
    m_board[x][y] = nullptr;
}

bool CheckersBoard::EmptyCell(coord_t coord) const
{
    CheckBounds(coord);

    return GetValueAt(coord) == nullptr;
}

void CheckersBoard::CheckBounds(coord_t coord) const
{
    const auto& [x, y] = coord;
    if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
    {
        throw std::out_of_range("x or y is out of range");
    }
}

bool CheckersBoard::IsOpponentPiece(coord_t srcCoord, coord_t dstCoord) const
{
    CheckBounds(srcCoord);
    CheckBounds(dstCoord);

    if (GetValueAt(srcCoord) == nullptr || GetValueAt(dstCoord) == nullptr)
        return false;
    if (GetValueAt(srcCoord)->GetSymbol() == GetValueAt(dstCoord)->GetSymbol())
        return false;
    
    return true;
}

std::unique_ptr<CheckersPiece> CheckersBoard::CreatePiece(coord_t coord, char color) const
{
    if (color == BLACK)
        return CreateBlackPiece(coord);
    else if (color == WHITE)
        return CreateWhitePiece(coord);
    else throw std::invalid_argument("Invalid color");
}
std::unique_ptr<CheckersPiece> CheckersBoard::CreateBlackPiece(coord_t coord) const
{
    return std::make_unique<CheckersPiece>(coord, m_players[GameConstants::PLAYER_TWOID], BLACK);
}
std::unique_ptr<CheckersPiece> CheckersBoard::CreateWhitePiece(coord_t coord) const
{
    return std::make_unique<CheckersPiece>(coord, m_players[GameConstants::PLAYER_ONEID], WHITE);
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