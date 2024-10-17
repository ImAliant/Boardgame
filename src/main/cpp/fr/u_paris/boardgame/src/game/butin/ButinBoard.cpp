#include "game/butin/ButinBoard.hpp"
#include "game/butin/ButinPiece.hpp"
#include "constants/Constants.hpp"

#include <algorithm>
#include <random>

using namespace Constants::Game::Butin;

ButinBoard::ButinBoard(): Board(BOARD_WIDTH, BOARD_HEIGHT)
{
    FillBoard();
}

void ButinBoard::FillBoard()
{
    if (GetHeight()*GetWidth() != RED_PIECE_NUMBER + YELLOW_PIECE_NUMBER + BLACK_PIECE_NUMBER)
    {
        return;
    }

    std::vector<char> symbols;
    GenerateSymbols(symbols);
    ShuffleSymbols(symbols);
    CreatePieces(symbols);
}

void ButinBoard::ShuffleSymbols(std::vector<char>& symbols) const
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(symbols.begin(), symbols.end(), g);
}

void ButinBoard::CreatePieces(const std::vector<char>& symbols)
{
    for (int i = 0; i < GetHeight(); i++)
    {
        for (int j = 0; j < GetWidth(); j++)
        {
            CreatePiece(coord_t{i,j}, symbols[i*GetWidth() + j]);
        }
    }
}

void ButinBoard::GenerateSymbols(std::vector<char>& symbols)
{
    const to_fill_t to_fill = {
        {RED_PIECE_SYMBOL, RED_PIECE_NUMBER},
        {YELLOW_PIECE_SYMBOL, YELLOW_PIECE_NUMBER},
        {BLACK_PIECE_SYMBOL, BLACK_PIECE_NUMBER}
    };

    for (const auto& [symbol, number]: to_fill)
    {
        for (int i = 0; i < number; i++)
        {
            symbols.push_back(symbol);
        }
    }
}

void ButinBoard::CreatePiece(const coord_t coord, const char symbol)
{
    SetPiece(coord, std::make_shared<ButinPiece>(coord, symbol));
}