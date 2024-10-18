#include "game/butin/ButinPiece.hpp"
#include "constants/Constants.hpp"
#include "game/movement/CoordUtils.hpp"

using namespace Constants::Game::Butin;

ButinPiece::ButinPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

void ButinPiece::FindMoves(std::shared_ptr<Board> board) 
{
    if (IsBlack() || IsRed()) return;

    for (const auto& dir: PIECE_DIRECTIONS)
    {
        coord_t new_coord = CoordUtils::CalculateNewCoord(GetCoord(), dir);
        
        if (!board->IsInBoard(new_coord) 
        || board->IsEmpty(new_coord)) continue;

        HandlePieceEncounter(new_coord, dir, board);
    }
}

void ButinPiece::HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board)
{
    const std::shared_ptr<ButinPiece> piece = std::dynamic_pointer_cast<ButinPiece>(board->GetPiece(to));
    coord_t jump_coord = CoordUtils::CalculateNewCoord(to, dir);
    if (!board->IsMoveValid(to, jump_coord)) return;

    AddPossibleMove(std::make_shared<Move>(jump_coord, piece));
}

bool ButinPiece::IsBlack() const
{
    return GetSymbol() == BLACK_PIECE_SYMBOL;
}

bool ButinPiece::IsRed() const
{
    return GetSymbol() == RED_PIECE_SYMBOL;
}

bool ButinPiece::IsYellow() const
{
    return GetSymbol() == YELLOW_PIECE_SYMBOL;
}