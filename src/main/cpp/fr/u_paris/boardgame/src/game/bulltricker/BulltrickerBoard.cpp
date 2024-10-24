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
    SetColor(BLACK_KING_COORD, BLACK);
    SetKing(BLACK_KING_COORD);

    CreatePiece(WHITE_KING_COORD, WHITE_KING_SYMBOL);
    SetColor(WHITE_KING_COORD, WHITE);
    SetKing(WHITE_KING_COORD);
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
                SetColor(coord, BLACK);
            }
            else if (i == WHITE_QUEEN_X)
            {
                CreatePiece(coord, WHITE_QUEEN_SYMBOL);
                SetColor(coord, WHITE);
            }
            SetQueen(coord);
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
                SetColor(coord, BLACK);
            }
            else if (i == WHITE_HORIZONTAL_PAWN_X)
            {
                CreatePiece(coord, WHITE_PAWN_SYMBOL);
                SetColor(coord, WHITE);
            }
            SetOrientation(coord, HORIZONTAL);
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
                SetColor(coord, BLACK);
            }
            else if (i == WHITE_VERTICAL_PAWN_X)
            {
                CreatePiece(coord, WHITE_PAWN_SYMBOL);
                SetColor(coord, WHITE);
            }
            SetOrientation(coord, VERTICAL);
        }
    }
}

std::shared_ptr<BulltrickerPiece> BulltrickerBoard::GetSpecificKing(const Color c) const
{
    for (int i{0}; i < GetHeight(); i++)
    {
        for (int j{0}; j < GetWidth(); j++)
        {
            const coord_t coord{i, j};

            if (std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->IsKing()
            && std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->GetColor() == c)
            {
                return std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord));
            }
        }
    }

    return nullptr;
}

void BulltrickerBoard::SetOrientation(const coord_t coord, const Orientation o) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->SetOrientation(o);
}

void BulltrickerBoard::SetColor(const coord_t coord, const Color c) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->SetColor(c);
}

void BulltrickerBoard::SetKing(const coord_t coord) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->SetType(KING);
}

void BulltrickerBoard::SetQueen(const coord_t coord) const
{
    std::dynamic_pointer_cast<BulltrickerPiece>(GetPiece(coord))->SetType(QUEEN);
}