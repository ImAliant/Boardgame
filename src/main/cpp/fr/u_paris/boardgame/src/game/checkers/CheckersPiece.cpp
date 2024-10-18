#include "game/checkers/CheckersPiece.hpp"
#include "constants/Constants.hpp"
#include "game/movement/CoordUtils.hpp"

using namespace Constants::Game::Checkers;

CheckersPiece::CheckersPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

void CheckersPiece::FindMoves(std::shared_ptr<Board> board)
{
    std::vector<dir_t> directions;
    if (IsQueen()) directions = QUEEN_PIECE_DIRECTIONS;
    else if (IsBlack()) directions = BLACK_PIECE_DIRECTIONS;
    else directions = WHITE_PIECE_DIRECTIONS;

    for (const auto& dir: directions)
    {
        coord_t new_coord = CoordUtils::CalculateNewCoord(GetCoord(), dir);
        if (!board->IsInBoard(new_coord)) continue;

        // Find if the new coord has a piece
        if (board->IsEmpty(new_coord))
        {
            AddPossibleMoveForEmptySpace(new_coord);
        }
        else {
            HandlePieceEncounter(new_coord, dir, board);
        }
    }
}

void CheckersPiece::AddPossibleMoveForEmptySpace(const coord_t& to)
{
    AddPossibleMove(std::make_shared<Move>(to));
}

void CheckersPiece::HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board)
{
    const std::shared_ptr<CheckersPiece> piece = std::dynamic_pointer_cast<CheckersPiece>(board->GetPiece(to));

    if (piece->IsBlack() == IsBlack()) return;

    coord_t jump_coord = CoordUtils::CalculateNewCoord(to, dir);
    if (!board->IsMoveValid(to, jump_coord)) return;

    AddPossibleMove(std::make_shared<Move>(jump_coord, piece));
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