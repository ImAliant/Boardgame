#include "../include/ButinPiece.hpp"
#include "../include/Constants.hpp"

ButinPiece::ButinPiece(int x, int y, char symbol)
    : Piece(x, y, nullptr, symbol)
{}

ButinPiece::~ButinPiece() {}

void ButinPiece::FindPossibleMoves(const Board& board)
{
    
    const auto& butinBoard = dynamic_cast<const ButinBoard&>(board);

    m_possibleMoves.clear();

    const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // Linear
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1} // Diagonal
    };

    for (const auto& dir : directions) {
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
    }

}


bool ButinPiece::IsWithinBoard(const ButinBoard& board, int x, int y) const
{
    return x >= 0 && x < board.GetRows() && y >= 0 && y < board.GetCols();
}


bool ButinPiece::EmptyCell(const ButinBoard& board, int x, int y) const
{
    return IsWithinBoard(board, x, y) && board.EmptyCell(x, y);
}

std::ostream& operator<<(std::ostream& os, const ButinPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}


bool ButinPiece::HasPieceToJump(const ButinBoard& board,int currentX, int currentY, int nextX, int nextY) {
    // Calculate the position of the piece to jump over
    int jumpX = (currentX + nextX) / 2;
    int jumpY = (currentY + nextY) / 2;

    // Check if the position to jump over is within bounds
    if (!IsWithinBoard(board,jumpX, jumpY)) 
    {
        return false;
    }

    char pieceColor = board.GetValueAt(jumpX, jumpY)->GetSymbol();
    return pieceColor != 'T'; 
}