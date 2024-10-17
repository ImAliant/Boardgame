#include "game/bulltricker/BulltrickerBoard.hpp"
#include "game/bulltricker/BulltrickerPiece.hpp"
#include "constants/Constants.hpp"

#include <iostream>

using namespace Constants::Game::Bulltricker;

BulltrickerBoard::BulltrickerBoard(): Board(BOARD_WIDTH, BOARD_HEIGHT)
{
    FillBoard();
}

void BulltrickerBoard::FillBoard()
{
    CreateKings();
    CreateQueens();
    CreateHorizontalPawns();
    CreateVerticalPawns();
}

void BulltrickerBoard::CreatePiece(const coord_t coord, const char symbol)
{
    SetPiece(coord, std::make_shared<BulltrickerPiece>(coord, symbol));
}

void BulltrickerBoard::CreateKings()
{
    CreatePiece(BLACK_KING_COORD, BLACK_KING_SYMBOL);
    CreatePiece(WHITE_KING_COORD, WHITE_KING_SYMBOL);
}

void BulltrickerBoard::CreateQueens()
{
    for (int i{0}; i < GetHeight(); i++)
    {
        for (int j{0}; j < GetWidth(); j++)
        {
            if (j == BLACK_KING_COORD.second 
            || j == WHITE_KING_COORD.second
            || (i+j)%2 == 0)
            {
                continue;
            }

            const coord_t coord{i, j};

            if (i == BLACK_QUEEN_X)
            {
                CreatePiece(coord, BLACK_QUEEN_SYMBOL);
                SetBlack(coord, true);
            }
            else if (i == WHITE_QUEEN_X)
            {
                CreatePiece(coord, WHITE_QUEEN_SYMBOL);
            }
        }
    }
}

void BulltrickerBoard::CreateHorizontalPawns()
{
    for (int i{0}; i < GetHeight(); i++)
    {
        for (int j{0}; j < GetWidth(); j++)
        {
            if ((i+j)%2 == 0)
            {
                continue;
            }

            const coord_t coord{i, j};

            if (i == BLACK_HORIZONTAL_PAWN_X)
            {
                CreatePiece(coord, BLACK_PAWN_SYMBOL);
                SetHorizontal(coord, true);
                SetBlack(coord, true);
            }
            else if (i == WHITE_HORIZONTAL_PAWN_X)
            {
                CreatePiece(coord, WHITE_PAWN_SYMBOL);
            }
        }
    }
}

void BulltrickerBoard::CreateVerticalPawns()
{
    for (int i{0}; i < GetHeight(); i++)
    {
        for (int j{0}; j < GetWidth(); j++)
        {
            if ((i+j)%2 == 0)
            {
                continue;
            }

            const coord_t coord{i, j};

            if (i == BLACK_VERTICAL_PAWN_X)
            {
                CreatePiece(coord, BLACK_PAWN_SYMBOL);
                SetBlack(coord, true);
            }
            else if (i == WHITE_VERTICAL_PAWN_X)
            {
                CreatePiece(coord, WHITE_PAWN_SYMBOL);
            }
        }
    }
}

void BulltrickerBoard::SetHorizontal(const coord_t coord, const bool h) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->SetHorizontal(h);
}

void BulltrickerBoard::SetBlack(const coord_t coord, const bool b) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->SetBlack(b);
}