#include "../../../include/game/checkers/CheckersPiece.hpp"

CheckersPiece::CheckersPiece(coord_t coord, std::shared_ptr<Player> owner, char symbol)
    : Piece(coord, std::move(owner), symbol)
{
    m_state.type = PieceType::PAWN;
}

CheckersPiece::~CheckersPiece() {}

void CheckersPiece::FindPossibleMoves(const Board& board)
{
    const auto& checkersBoard = dynamic_cast<const CheckersBoard&>(board);

    m_possibleMoves.clear();
    m_possibleCaptures.clear();

    CaptureMoves(checkersBoard);

    if (m_possibleCaptures.empty())
        SimpleMoves(checkersBoard);
}

void CheckersPiece::SimpleMoves(const CheckersBoard& board) 
{
    const auto white = GameConstants::CheckersConstants::WHITE;
    const auto black = GameConstants::CheckersConstants::BLACK;
    const auto& wdir = GameConstants::CheckersConstants::WHITE_DIRECTION;
    const auto& bdir = GameConstants::CheckersConstants::BLACK_DIRECTION;

    std::vector<direction_t> const* directions;
    if (m_state.type == PieceType::PAWN)
    {
        if (m_state.m_symbol == white)
            directions = &wdir;
        else if (m_state.m_symbol == black)
            directions = &bdir;
        else
            return; 
    }
    else 
    {
        directions = &GameConstants::CheckersConstants::ALL_DIRECTION;
    }

    AddPossibleMoves(board, *directions);
}

void CheckersPiece::AddPossibleMoves(const CheckersBoard& board, std::vector<direction_t> const& directions)
{
    for (const auto& [dx, dy]: directions)
    {
        int x = GetX() + dx;
        int y = GetY() + dy;

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
    std::vector<direction_t> const* directions = &GameConstants::CheckersConstants::ALL_DIRECTION;

    if (m_state.type == PieceType::PAWN)
    {
        for (const auto& [dx, dy]: *directions)
        {
            int x = GetX() + 2*dx;
            int y = GetY() + 2*dy;

            const auto& coord = std::make_pair(x, y);
            const auto& coord1 = std::make_pair(GetX() + dx, GetY() + dy);
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
    const auto& [dx, dy] = dir;
    int x = GetX() + dx;
    int y = GetY() + dy;

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
        const auto& piece = board.GetValueAt(coord);
        if (piece == nullptr) return false;
        auto pieceColor = piece->GetSymbol();
        return pieceColor != m_state.m_symbol;
    }

    return false;
}
bool CheckersPiece::IsEmptyCell(const CheckersBoard& board, const coord_t coord) const
{
    return IsWithinBoard(board, coord) && board.EmptyCell(coord);
}

void CheckersPiece::Promote()
{
    m_state.type = PieceType::QUEEN;
}

bool CheckersPiece::IsPromoted() const
{
    return m_state.type == PieceType::QUEEN;
}

std::vector<direction_t> CheckersPiece::GetPossibleCaptures() const
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