#include "../../../include/game/checkers/CheckersBoard.hpp"

using namespace GameConstants::CheckersConstants;

CheckersBoard::CheckersBoard(std::vector<std::shared_ptr<Player>> players): 
    Board(std::move(players), CHECKERSROWS, CHECKERSCOLS)
{
    Init();
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

bool CheckersBoard::IsOpponentPiece(coord_t srcCoord, coord_t dstCoord) const
{
    CheckBounds(srcCoord);
    CheckBounds(dstCoord);

    if (IsEmptyCell(srcCoord) || IsEmptyCell(dstCoord))
        return false;
    const auto srcPiece = GetPiece(srcCoord);
    const auto dstPiece = GetPiece(dstCoord);
    if (srcPiece->GetSymbol() == dstPiece->GetSymbol())
        return false;
    
    return true;
}

std::unique_ptr<Piece> CheckersBoard::CreatePiece(coord_t coord, char color) const
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
            if (board.m_board[i][j] == nullptr)
                os << " ";
            else
                os << board.m_board[i][j]->GetSymbol();
        }
        os << std::endl;
    }
    return os;
}