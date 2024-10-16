#include "game/checkers/CheckersBoard.hpp"

CheckersBoard::CheckersBoard(): Board(10, 10) {
    FillBoard();
}

void CheckersBoard::FillBoard()
{
    for (int i{0}; i < GetHeight(); i++)
    {
        for (int j{0}; j < GetWidth(); j++)
        {
            if (i < 4 && (i + j) % 2 != 0)
            {
                SetPiece(i, j, std::make_shared<Piece>(coord_t{i, j}, 'O'));
            }
            else if (i > 5 && (i + j) % 2 != 0)
            {
                SetPiece(i, j, std::make_shared<Piece>(coord_t{i, j}, 'X'));
            }
            else
            {
                SetPiece(i, j, nullptr);
            }
        }
    }
}