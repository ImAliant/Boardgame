#include "game/checkers/CheckersPiece.hpp"
#include "constants/Constants.hpp"


using namespace Constants::Game::Checkers;

CheckersPiece::CheckersPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

void CheckersPiece::FindSimpleMoves(std::shared_ptr<Board> board)
{
    std::vector<dir_t> directions;
    if (IsQueen()) directions = QUEEN_PIECE_DIRECTIONS;
    else if (IsBlack()) directions = BLACK_PIECE_DIRECTIONS;
    else directions = WHITE_PIECE_DIRECTIONS;

    // TODO
}

void CheckersPiece::FindJumpMoves(std::shared_ptr<Board> board)
{

}

bool CheckersPiece::IsBlack() const
{
    return GetSymbol() == BLACK_PIECE_SYMBOL;
}

bool CheckersPiece::IsQueen() const
{
    return type == QUEEN;
}

void CheckersPiece::Upgrade()
{
    if (type != PAWN) return;
    type = QUEEN;
}

PieceType CheckersPiece::GetType() const
{
    return type;
}   