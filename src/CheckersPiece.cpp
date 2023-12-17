#include "../include/CheckersPiece.hpp"

CheckersPiece::CheckersPiece(int x, int y, std::shared_ptr<Player> owner, char symbol)
    : Piece(x, y, std::move(owner), symbol)
{
    m_state.type = PieceType::PAWN;
}

CheckersPiece::~CheckersPiece() {}

void CheckersPiece::FindPossibleMoves(const Board& board)
{
    const auto& checkersBoard = dynamic_cast<const CheckersBoard&>(board);

    if (m_state.m_symbol == CheckersConstants::TRANSPARENT) return;

    m_possibleMoves.clear();
    m_possibleCaptures.clear();

    SimpleMoves(checkersBoard);
    CaptureMoves(checkersBoard);
}
void CheckersPiece::SimpleMoves(const CheckersBoard& board) 
{
    std::vector<std::pair<int, int>> const* directions;
    if (m_state.m_symbol == CheckersConstants::WHITE)
        directions = &CheckersConstants::WHITE_DIRECTION;
    else if (m_state.m_symbol == CheckersConstants::BLACK)
        directions = &CheckersConstants::BLACK_DIRECTION;
    else
        return;

    for (const auto& [dx, dy] : *directions)
    {
        int x = m_x + dx;
        int y = m_y + dy;

        if (!IsWithinBoard(board, x, y)) continue;
    
        if (board.EmptyCell(x, y))
        {
            m_possibleMoves.push_back(std::make_pair(x, y));
        }
    }
}
void CheckersPiece::CaptureMoves(const CheckersBoard& board)
{
    // Un joueur peut capturer une pièce adverse dans n'importe quelle directions

    std::vector<std::pair<int, int>> const* directions = &CheckersConstants::ALL_DIRECTION;

    // On verifie dans ces directions si une piece adverse peut etre capturée
    for (const auto& [dx, dy]: *directions)
    {
        int x = m_x + 2*dx;
        int y = m_y + 2*dy;

        if (IsWithinBoard(board, x, y) && IsOpponentPiece(board, m_x + dx, m_y + dy) && EmptyCell(board, x, y))
        {
            m_possibleMoves.push_back(std::make_pair(x, y));
            m_possibleCaptures.push_back(std::make_pair(dx, dy));
        }
    }
}

bool CheckersPiece::IsWithinBoard(const CheckersBoard& board, int x, int y) const
{
    return x >= 0 && x < board.GetRows() && y >= 0 && y < board.GetCols();
}
bool CheckersPiece::IsOpponentPiece(const CheckersBoard& board, int x, int y) const
{
    if (IsWithinBoard(board, x, y)) 
    {
        auto pieceColor = board.GetValueAt(x, y)->GetSymbol();
        return !board.EmptyCell(x, y) && pieceColor != m_state.m_symbol;
    }

    return false;
}
bool CheckersPiece::EmptyCell(const CheckersBoard& board, int x, int y) const
{
    return IsWithinBoard(board, x, y) && board.EmptyCell(x, y);
}

void CheckersPiece::SetCanBeCaptured()
{
    m_canBeCaptured = true;
}
void CheckersPiece::ResetCanBeCaptured()
{
    m_canBeCaptured = false;
}

void CheckersPiece::Promote()
{
    m_state.type = PieceType::QUEEN;
}

bool CheckersPiece::IsPromoted() const
{
    return m_state.type == PieceType::QUEEN;
}

bool CheckersPiece::CanBeCaptured() const
{
    return m_canBeCaptured;
}

std::vector<std::pair<int, int>> CheckersPiece::GetPossibleCaptures() const
{
    return m_possibleCaptures;
}

std::string CheckersPiece::GetType() const
{
    std::string res;
    if (m_state.type == PAWN) res = "PAWN";
    else if (m_state.type == QUEEN) res = "QUEEN";
    else res = "EMPTY";

    return res;
}

std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}