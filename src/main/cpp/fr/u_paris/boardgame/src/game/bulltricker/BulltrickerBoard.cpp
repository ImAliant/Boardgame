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

void BulltrickerBoard::CreatePiece(const int i, const int j, const char symbol)
{
    SetPiece(i, j, std::make_shared<BulltrickerPiece>(coord_t{i, j}, symbol));
}

void BulltrickerBoard::CreateKings()
{
    CreatePiece(BLACK_KING_COORD.first, BLACK_KING_COORD.second, BLACK_KING_SYMBOL);
    CreatePiece(WHITE_KING_COORD.first, WHITE_KING_COORD.second, WHITE_KING_SYMBOL);
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

            if (i == BLACK_QUEEN_X)
            {
                CreatePiece(i, j, BLACK_QUEEN_SYMBOL);
            }
            else if (i == WHITE_QUEEN_X)
            {
                CreatePiece(i, j, WHITE_QUEEN_SYMBOL);
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

            if (i == BLACK_HORIZONTAL_PAWN_X)
            {
                CreatePiece(i, j, BLACK_PAWN_SYMBOL);
                SetHorizontal(i, j, true);
            }
            else if (i == WHITE_HORIZONTAL_PAWN_X)
            {
                CreatePiece(i, j, WHITE_PAWN_SYMBOL);
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

            if (i == BLACK_VERTICAL_PAWN_X)
            {
                CreatePiece(i, j, BLACK_PAWN_SYMBOL);
            }
            else if (i == WHITE_VERTICAL_PAWN_X)
            {
                CreatePiece(i, j, WHITE_PAWN_SYMBOL);
            }
        }
    }
}

void BulltrickerBoard::SetHorizontal(const int i, const int j, const bool h) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord_t{i, j}))->SetHorizontal(h);
}