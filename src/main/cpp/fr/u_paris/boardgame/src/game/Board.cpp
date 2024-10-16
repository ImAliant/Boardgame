#include "game/Board.hpp"

Board::Board(const int w, const int h): width{w}, height{h}
{
    Init();
}

void Board::Init()
{
    pieces.resize(height);
    for (int i = 0; i < height; i++)
    {
        pieces[i].resize(width);
    }
}

void Board::FillBoard()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pieces[i][j] = nullptr;
        }
    }
}

void Board::MovePiece(const coord_t from, const coord_t to)
{
    if (IsEmpty(from) || IsEmpty(to) 
    || !IsInBoard(from) || !IsInBoard(to))
    {
        return;
    }

    SetPiece(to.first, to.second, GetPiece(from));
    RemovePiece(from);
}

void Board::RemovePiece(const coord_t coord) 
{
    if (IsEmpty(coord) || !IsInBoard(coord))
    {
        return;
    }

    SetPiece(coord.first, coord.second, nullptr);
}

void Board::CreatePiece(const int i, const int j, const char symbol)
{
    SetPiece(i, j, std::make_shared<Piece>(coord_t{i, j}, symbol));
}

void Board::SetPiece(const int x, const int y, std::shared_ptr<Piece> p)
{
    pieces[x][y] = p;
}

std::shared_ptr<Piece> Board::GetPiece(const coord_t coord) const
{
    if (!IsInBoard(coord))
    {
        return nullptr;
    }

    return pieces[coord.first][coord.second];
}

bool Board::IsEmpty(const coord_t coord) const
{
    return GetPiece(coord) == nullptr;
}

bool Board::IsInBoard(const coord_t coord) const
{
    return coord.first >= 0 && coord.first < height
        && coord.second >= 0 && coord.second < width;
}

int Board::GetWidth() const
{
    return width;
}

int Board::GetHeight() const
{
    return height;
}

std::vector<std::vector<std::shared_ptr<Piece>>> Board::GetPieces() const
{
    return pieces;
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for (int i = 0; i < b.GetHeight(); i++)
    {
        for (int j = 0; j < b.GetWidth(); j++)
        {
            if (b.IsEmpty({i, j}))
            {
                os << ".";
            }
            else
            {
                os << b.GetPiece({i, j})->GetSymbol();
            }
        }
        os << std::endl;
    }

    return os;
}
