#include "../../../include/game/bulltricker/BulltrickerBoard.hpp"

using namespace GameConstants::BulltrickerConstants;
BulltrickerBoard::BulltrickerBoard(std::vector<std::shared_ptr<Player>> players):
    Board{std::move(players), BULLTRICKERROWS, BULLTRICKERCOLS}
{
    Init();
}

void BulltrickerBoard::FillBoard()
{
    for (int i = 9; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            const auto& coord = std::make_pair(i, j);
            // Placement of black pieces
            if (i > 0 && i < 4)
            {
                if (i == 1 && j%2 == 0)
                    m_board[i][j] = CreatePiece(coord, BLACK);
                else if (i == 2 && j%2 != 0)
                    m_board[i][j] = CreatePiece(coord, BLACK);
                else if (i == 3 && j%2 == 0)
                    m_board[i][j] = CreatePiece(coord, BLACK);
            }

            // Placement of white pieces
            else if (i > 10 && i < 15)
            {
                if (i == 11 && j%2 == 0)
                    m_board[i][j] = CreatePiece(coord, WHITE);
                else if (i == 12 && j%2 != 0)
                    m_board[i][j] = CreatePiece(coord, WHITE);
                else if (i == 13 && j%2 == 0)
                    m_board[i][j] = CreatePiece(coord, WHITE);
            }
        }
    }

    // Placement of the king
    m_board[1][8] = CreatePiece(std::make_pair(1, 8), BLACK);
    m_board[13][8] = CreatePiece(std::make_pair(13, 8), WHITE);
}

std::unique_ptr<Piece> BulltrickerBoard::CreatePiece(const coord_t coord, const char color) const
{
    const auto& [row, col] = coord;
    if (color == BLACK)
    {
        // King
        if (row == 1 && col == 8)
            return CreateBlackPiece(coord, true, false);
        // Queen
        else if (row == 1 && col%2 == 0)
            return CreateBlackPiece(coord, false, true);
        // Normal piece
        else
            return CreateBlackPiece(coord, false, false);
    }
    else if (color == WHITE)
    {
        // King
        if (row == 13 && col == 8)
            return CreateWhitePiece(coord, true, false);
        // Queen
        else if (row == 13 && col%2 == 0)
            return CreateWhitePiece(coord, false, true);
        // Normal piece
        else
            return CreateWhitePiece(coord, false, false);
    }
    else throw std::invalid_argument("Invalid color");
}

std::unique_ptr<BulltrickerPiece> BulltrickerBoard::CreateBlackPiece(const coord_t coord, bool king, bool queen) const
{
    return std::make_unique<BulltrickerPiece>(coord, m_players[GameConstants::PLAYER_TWOID],BLACK, king, queen);
}

std::unique_ptr<BulltrickerPiece> BulltrickerBoard::CreateWhitePiece(const coord_t coord, bool king, bool queen) const
{
    return std::make_unique<BulltrickerPiece>(coord, m_players[GameConstants::PLAYER_ONEID],WHITE, king, queen);
}