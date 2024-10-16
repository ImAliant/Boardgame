#include "game/checkers/CheckersBoard.hpp"
#include "game/checkers/CheckersPiece.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::Checkers;

CheckersBoard::CheckersBoard(): Board(BOARD_WIDTH, BOARD_HEIGHT) {
    FillBoard();
}

void CheckersBoard::FillBoard()
{
    for (int i{0}; i < GetHeight(); i++)
    {
        for (int j{0}; j < GetWidth(); j++)
        {
            if (i < BLACK_PIECE_ROW && (i + j) % 2 != 0)
            {
                CreateBlackPiece(i, j);
            }
            else if (i > WHITE_PIECE_ROW && (i + j) % 2 != 0)
            {
                CreateWhitePiece(i, j);
            }
            else
            {
                SetPiece(i, j, nullptr);
            }
        }
    }
}

void CheckersBoard::CreateBlackPiece(const int i, const int j)
{
    CreatePiece(i, j, BLACK_PIECE_SYMBOL);
}

void CheckersBoard::CreateWhitePiece(const int i, const int j)
{
    CreatePiece(i, j, WHITE_PIECE_SYMBOL);
}

void CheckersBoard::CreatePiece(const int i, const int j, const char symbol)
{
    SetPiece(i, j, std::make_shared<CheckersPiece>(coord_t{i, j}, symbol));
}