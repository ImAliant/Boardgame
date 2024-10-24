#include "game/bulltricker/BulltrickerPiece.hpp"
#include "game/bulltricker/BulltrickerBoard.hpp"
#include "game/movement/CoordUtils.hpp"

using namespace Constants::Game::Bulltricker;

BulltrickerPiece::BulltrickerPiece(
    const coord_t c, 
    const char s): Piece{c, s} {}

void BulltrickerPiece::FindMoves(std::shared_ptr<Board> board)
{
    /* if(IsKing())
    {
        FindKingMoves(board);
    }
    else if(IsQueen())
    {
        FindQueenMoves(board);
    }
    else
    {
        FindPawnMoves(board);
    } */
}

void BulltrickerPiece::FindKingMoves(std::shared_ptr<Board> board)
{
    /* for (const auto& dir: KING_DIRECTIONS)
    {
        const coord_t neighbour{CoordUtils::CalculateNewCoord(GetCoord(), dir)};
        if (!board->IsCoordValid(neighbour)) continue;

        const coord_t kingcell = CoordUtils::CalculateNewCoord(neighbour, dir);
        if (!board->IsCoordValid(kingcell)) continue;

        // On verifie si dans les cases royales autour de la case de destination ne présente pas le roi adverse
        const std::shared_ptr<BulltrickerBoard> b = std::dynamic_pointer_cast<BulltrickerBoard>(board);
        const std::shared_ptr<BulltrickerPiece> opponentKing = b->GetSpecificKing(GetColor() == BLACK ? WHITE : BLACK);

        std::vector<coord_t> neighbours = CoordUtils::GetNeighbours(neighbour, 2, board);
        bool found = false;
        for (const auto& n: neighbours)
        {
            // Si on trouve le roi adverse dans les cases royales autour de la case de destination
            // On passe a la prochaine direction
            if (n == opponentKing->GetCoord())
            {
                found = true;
                break;
            }
        }

        if (found) continue;

        
    } */
}

void BulltrickerPiece::FindQueenMoves(std::shared_ptr<Board> board)
{

}

void BulltrickerPiece::FindPawnMoves(std::shared_ptr<Board> board)
{

}

void BulltrickerPiece::HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board)
{

}

void BulltrickerPiece::Upgrade()
{
    if (!IsPawn()) return;

    type = QUEEN;
}

void BulltrickerPiece::SwitchOrientation()
{
    orientation = (orientation == HORIZONTAL) ? VERTICAL : HORIZONTAL;
}

bool BulltrickerPiece::IsHorizontal() const
{
    return orientation == HORIZONTAL;
}

bool BulltrickerPiece::IsBlack() const
{
    return color == BLACK;
}

bool BulltrickerPiece::IsKing() const
{
    return type == KING;
}

bool BulltrickerPiece::IsQueen() const
{
    return type == QUEEN;
}

bool BulltrickerPiece::IsPawn() const
{
    return type == PAWN;
}

Orientation BulltrickerPiece::GetOrientation() const
{
    return orientation;
}

Color BulltrickerPiece::GetColor() const
{
    return color;
}

PieceType BulltrickerPiece::GetType() const
{
    return type;
}

void BulltrickerPiece::SetOrientation(const Orientation o)
{
    orientation = o;
}

void BulltrickerPiece::SetColor(const Color c)
{
    color = c;
}

void BulltrickerPiece::SetType(const PieceType t)
{
    type = t;
}