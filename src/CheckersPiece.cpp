#include "../include/CheckersPiece.hpp"

CheckersPiece::CheckersPiece(coord_t coord, std::shared_ptr<Player> owner, char symbol)
    : Piece(coord, std::move(owner), symbol)
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
    std::vector<direction_t> const* directions;
    if (m_state.type == PieceType::PAWN)
    {
        if (m_state.m_symbol == CheckersConstants::WHITE)
            directions = &CheckersConstants::WHITE_DIRECTION;
        else if (m_state.m_symbol == CheckersConstants::BLACK)
            directions = &CheckersConstants::BLACK_DIRECTION;
        else
            return; 
    }
    else 
    {
        directions = &CheckersConstants::ALL_DIRECTION;
    }

    AddPossibleMoves(board, *directions);
}

void CheckersPiece::AddPossibleMoves(const CheckersBoard& board, std::vector<direction_t> const& directions)
{
    for (const auto& [dx, dy]: directions)
    {
        int x = m_x + dx;
        int y = m_y + dy;

        auto coord = std::make_pair(x, y);
        while (IsWithinBoard(board, coord) && IsEmptyCell(board, coord))
        {
            const auto& move = std::make_pair(x, y);
            m_possibleMoves.push_back(move);
            
            if (!IsPromoted()) break;
            
            x += dx;
            y += dy;

            coord = std::make_pair(x, y);
        }
    }
}

void CheckersPiece::CaptureMoves(const CheckersBoard& board)
{
    std::vector<direction_t> const* directions = &CheckersConstants::ALL_DIRECTION;

    if (m_state.type == PieceType::PAWN)
    {
        for (const auto& [dx, dy]: *directions)
        {
            int x = m_x + 2*dx;
            int y = m_y + 2*dy;

            const auto& coord = std::make_pair(x, y);
            const auto& coord1 = std::make_pair(m_x + dx, m_y + dy);
            if (IsWithinBoard(board, coord) && IsOpponentPiece(board, coord1) && IsEmptyCell(board, coord))
            {
                const auto& direction = std::make_pair(dx, dy);
                m_possibleMoves.push_back(coord);
                m_possibleCaptures.push_back(direction);
            }
        }
    }
    else
    {
        for (const auto& dir: *directions)
        {
            QueenCaptureDirections(board, dir);
        }
    }
}

void CheckersPiece::QueenCaptureDirections(const CheckersBoard& board, direction_t dir)
{
    /*const auto& [dx, dy] = dir;
    int x = m_x + dx;
    int y = m_y + dy;

    auto coord = std::make_pair(x, y);
    while (IsWithinBoard(board, coord) && IsEmptyCell(board, coord))
    {
        x += dx;
        y += dy;

        coord = std::make_pair(x, y);
    }

    const auto& coord1 = std::make_pair(x+dx, y+dy);
    if (IsWithinBoard(board, coord) && IsOpponentPiece(board, coord) && IsEmptyCell(board, coord1))
    {
        m_possibleMoves.push_back(coord1);
        m_possibleCaptures.push_back(std::make_pair(dx, dy));
    }*/

    const auto& [dx, dy] = dir;
    int x = m_x + dx;
    int y = m_y + dy;

    auto coord = std::make_pair(x, y);
    while (IsWithinBoard(board, coord) && IsEmptyCell(board, coord))
    {
        x += dx;
        y += dy;

        coord = std::make_pair(x, y);
    }

    if (IsWithinBoard(board, coord) && IsOpponentPiece(board, coord))
    {
        int captX = x + dx;
        int captY = y + dy;

        auto captCoord = std::make_pair(captX, captY);
        while (IsWithinBoard(board, captCoord) && IsEmptyCell(board, captCoord))
        {
            m_possibleMoves.push_back(captCoord);
            m_possibleCaptures.push_back(std::make_pair(dx, dy));

            captX += dx;
            captY += dy;

            captCoord = std::make_pair(captX, captY);
        }
    }
}

bool CheckersPiece::IsWithinBoard(const CheckersBoard& board, const coord_t coord) const
{
    const auto& [x, y] = coord;
    return x >= 0 && x < board.GetRows() && y >= 0 && y < board.GetCols();
}
bool CheckersPiece::IsOpponentPiece(const CheckersBoard& board, const coord_t coord) const
{
    if (IsWithinBoard(board, coord)) 
    {
        auto pieceColor = board.GetValueAt(coord)->GetSymbol();
        return !IsEmptyCell(board, coord) && pieceColor != m_state.m_symbol;
    }

    return false;
}
bool CheckersPiece::IsEmptyCell(const CheckersBoard& board, const coord_t coord) const
{
    return IsWithinBoard(board, coord) && board.EmptyCell(coord);
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