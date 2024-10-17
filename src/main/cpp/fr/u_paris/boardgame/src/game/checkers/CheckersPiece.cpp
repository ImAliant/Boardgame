#include "game/checkers/CheckersPiece.hpp"

CheckersPiece::CheckersPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

void CheckersPiece::SetPossibleMoves(std::shared_ptr<Board> board)
{

}