#include "game/butin/ButinPiece.hpp"

ButinPiece::ButinPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

void ButinPiece::FindMoves(std::shared_ptr<Board> board) {}