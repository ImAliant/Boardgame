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
            const coord_t coord{i, j};

            if (i < BLACK_PIECE_ROW && (i + j) % 2 != 0)
            {
                CreateBlackPiece(coord);
            }
            else if (i > WHITE_PIECE_ROW && (i + j) % 2 != 0)
            {
                CreateWhitePiece(coord);
            }
            else
            {
                SetPiece(coord, nullptr);
            }
        }
    }
}

void CheckersBoard::CreateBlackPiece(const coord_t coord)
{
    CreatePiece(coord, BLACK_PIECE_SYMBOL);
}

void CheckersBoard::CreateWhitePiece(const coord_t coord)
{
    CreatePiece(coord, WHITE_PIECE_SYMBOL);
}

void CheckersBoard::CreatePiece(const coord_t coord, const char symbol)
{
    SetPiece(coord, std::make_shared<CheckersPiece>(coord, symbol));
}