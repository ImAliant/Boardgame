#include "../../../include/game/butin/ButinPiece.hpp"
#include "../../../include/Constants.hpp"

ButinPiece::ButinPiece(coord_t coord, char symbol)
    : Piece(coord, nullptr, symbol)
{}

ButinPiece::~ButinPiece() {}

void ButinPiece::FindPossibleMoves(const Board& board)
{
    const auto& butinBoard = dynamic_cast<const ButinBoard&>(board);

    m_possibleMoves.clear();

    std::vector<direction_t> const* directions;
    directions = &GameConstants::ButinConstants::ALL_DIRECTION;

    /*for (const auto& dir : *directions) {
        int nextX = GetPosition().first+ dir.first;
        int nextY = GetPosition().second + dir.second;
        int landX = nextX + dir.first;
        int landY = nextY + dir.second;
            
        if (IsWithinBoard(butinBoard,nextX,nextY) && HasPieceToJump(butinBoard,GetPosition().first, GetPosition().second, landX, landY)) {
            if (IsWithinBoard(butinBoard,landX, landY) &&  
                EmptyCell(butinBoard,landX, landY)) {
                m_possibleMoves.push_back({landX, landY});
            }
        }
    }*/

    for (const auto& dir: *directions)
    {
        auto [dirX, dirY] = dir;
        auto [posX, posY] = GetPosition();
        int nextX = posX + dirX;
        int nextY = posY + dirY;
        int landX = nextX + dirX;
        int landY = nextY + dirY;

        const auto& next = std::make_pair(nextX, nextY);
        const auto& current = std::make_pair(posX, posY);
        const auto& land = std::make_pair(landX, landY);
        if (IsWithinBoard(butinBoard, next) && HasPieceToJump(butinBoard, current, land))
        {
            if (IsWithinBoard(butinBoard, land) && IsEmptyCell(butinBoard, land))
            {
                m_possibleMoves.push_back(land);
            }
        }
    }
}

bool ButinPiece::IsWithinBoard(const ButinBoard& board, const coord_t coord) const
{
    const auto& [x, y] = coord;
    return x >= 0 && x < board.GetRows() && y >= 0 && y < board.GetCols();
}

bool ButinPiece::IsEmptyCell(const ButinBoard& board, const coord_t coord) const
{
    return IsWithinBoard(board, coord) && board.EmptyCell(coord);
}

std::ostream& operator<<(std::ostream& os, const ButinPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}


bool ButinPiece::HasPieceToJump(const ButinBoard& board, coord_t current, coord_t next) const
{
    const int currentX = current.first;
    const int currentY = current.second;
    const int nextX = next.first;
    const int nextY = next.second;

    // Calculate the position of the piece to jump over
    int jumpX = (currentX + nextX) / 2;
    int jumpY = (currentY + nextY) / 2;

    const auto& coord = std::make_pair(jumpX, jumpY);
    // Check if the position to jump over is within bounds
    if (!IsWithinBoard(board, coord)) 
    {
        return false;
    }

    auto piece = board.GetValueAt(coord);
    return piece != nullptr;
}