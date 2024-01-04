#include "../../../include/game/bulltricker/BulltrickerBoard.hpp"

using namespace GameConstants::BulltrickerConstants;
BulltrickerBoard::BulltrickerBoard(std::vector<std::shared_ptr<Player>> players):
    Board{std::move(players), BULLTRICKERROWS, BULLTRICKERCOLS}
{
    Init();
}

void BulltrickerBoard::FillBoard()
{
    
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            const auto& coord = std::make_pair(i, j);
            //skip buttee
            if (i % 2 == 0 && j % 2 == 0) continue;
          
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
            else if (i > 10 && i < 14)
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
    m_board[1][7] = CreatePiece(std::make_pair(1, 7), BLACK);
    m_board[13][7] = CreatePiece(std::make_pair(13, 7), WHITE);
}

std::unique_ptr<Piece> BulltrickerBoard::CreatePiece(const coord_t coord, const char color) const {
    
    const auto& [row, col] = coord;
    bool isHorizontal = DetermineOrientation(row, col);
    if (color == BLACK)
    {
        // King
        if (row == 1 && col == 7)
            return CreateBlackPiece(coord, true, false,isHorizontal);
        // Queen
        else if (row == 1 && col%2 == 0)
            return CreateBlackPiece(coord, false, true,isHorizontal);
        // pawn
        else if (row == 2 && col%2 != 0)
            return CreateBlackPiece(coord, false, false,isHorizontal);
        else if (row == 3 && col%2 == 0)
            return CreateBlackPiece(coord, false, false,isHorizontal);
        
    }
    else if (color == WHITE)
    {
        // King
        if (row == 13 && col == 7)
            return CreateWhitePiece(coord, true, false,isHorizontal);
            
        // Queen
        else if (row == 13 && col%2 == 0)
            return CreateWhitePiece(coord, false, true,isHorizontal);
        // Normal piece
        else if (row == 12 && col%2 != 0)
            return CreateWhitePiece(coord, false, false,isHorizontal);
        else if (row == 11 && col%2 == 0)
            return CreateWhitePiece(coord, false, false,isHorizontal);
    }
  
  else throw std::invalid_argument("Invalid color");

}

std::unique_ptr<BulltrickerPiece> BulltrickerBoard::CreateBlackPiece(const coord_t coord, bool king, bool queen,bool isHorizontal) const
{
    return std::make_unique<BulltrickerPiece>(coord, m_players[GameConstants::PLAYER_TWOID],BLACK, king, queen,isHorizontal);
}

std::unique_ptr<BulltrickerPiece> BulltrickerBoard::CreateWhitePiece(const coord_t coord, bool king, bool queen,bool isHorizontal) const
{
    return std::make_unique<BulltrickerPiece>(coord, m_players[GameConstants::PLAYER_ONEID],WHITE, king, queen,isHorizontal);
}


bool BulltrickerBoard::DetermineOrientation(int row, int col) const {
    return row % 2 == 0;
}


std::ostream &operator<<(std::ostream &os, const BulltrickerBoard &board)
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