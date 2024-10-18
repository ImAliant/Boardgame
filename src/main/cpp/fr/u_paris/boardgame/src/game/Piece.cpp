#include "game/Piece.hpp"

Piece::Piece(const coord_t c, const char s): coord{c}, symbol{s} {}

void Piece::SetPossibleMoves(std::shared_ptr<Board> board)
{
    ClearPossibleMoves();

    FindMoves(board);
}

void Piece::AddPossibleMove(const std::shared_ptr<Move> m)
{
    possible_moves.push_back(m);
}

void Piece::ClearPossibleMoves()
{
    possible_moves.clear();
}

void Piece::SetCoord(const coord_t c)
{
    coord = c;
}

coord_t Piece::GetCoord() const
{
    return coord;
}

char Piece::GetSymbol() const
{
    return symbol;
}

std::vector<std::shared_ptr<Move>> Piece::GetPossibleMoves() const
{
    return possible_moves;
}
