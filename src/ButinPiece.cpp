#include "../include/ButinPiece.hpp"
#include "../include/Constants.hpp"

ButinPiece::ButinPiece(int x, int y, char symbol)
    : Piece(x, y, nullptr, symbol)
{}

ButinPiece::~ButinPiece() {}

void ButinPiece::FindPossibleMoves(const Board& board)
{
    
    const auto& butinBoard = dynamic_cast<const ButinBoard&>(board);

    //if (m_state.m_symbol != 'Y') return; // Only yellow pieces can move

    m_possibleMoves.clear();

    // Include diagonal directions in addition to linear
    const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // Linear
        {1, 1}, {-1, -1}, {1, -1}, {-1, 1} // Diagonal
    };

    for (const auto& dir : directions) {
        int nextX = GetPosition().first+ dir.first;
        int nextY = GetPosition().second + dir.second;
        int landX = nextX + dir.first;
        int landY = nextY + dir.second;
            
        // Check if next position is within bounds and has a piece to jump over
        if (IsWithinBoard(butinBoard,nextX,nextY) && HasPieceToJump(butinBoard,GetPosition().first, GetPosition().second, landX, landY)) {
            // Check if landing position is valid (within bounds and empty)
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

void ButinPiece::SetCanBeCaptured()
{
    m_canBeCaptured = true;
}
void ButinPiece::ResetCanBeCaptured()
{
    m_canBeCaptured = false;
}

bool ButinPiece::CanBeCaptured() const
{
    return m_canBeCaptured;
}

std::vector<std::pair<int, int>> ButinPiece::GetPossibleCaptures() const
{
    return m_possibleCaptures;
}

std::ostream& operator<<(std::ostream& os, const ButinPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}


bool ButinPiece::HasPieceToJump(const ButinBoard& board,int currentX, int currentY, int nextX, int nextY) {
    // Calculate the position of the piece to potentially jump over
    int jumpX = (currentX + nextX) / 2;
    int jumpY = (currentY + nextY) / 2;

    // Check if the position to jump over is within bounds
    if (!IsWithinBoard(board,jumpX, jumpY)) {
        return false;
    }
    

    // Get the color of the piece at the jump position
    char pieceColor = board.GetValueAt(jumpX, jumpY)->GetSymbol();
     

    // Check if there's a piece to jump over (non-yellow) at this position
    return pieceColor != 'T'; // 'Y' for yellow, 'T' for transparent/empty
}