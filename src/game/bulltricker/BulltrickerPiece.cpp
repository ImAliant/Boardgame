#include "../../../include/game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(const coord_t coord, const std::shared_ptr<Player> owner, 
                                   const char symbol, const int type, const bool isHorizontal):
    Piece{coord, owner, symbol}, m_isHorizontal{isHorizontal}
{
    m_state.m_type = type;
}
BulltrickerPiece::~BulltrickerPiece(){}

void BulltrickerPiece::FindPossibleMoves(const Board& board)
{
    Piece::FindPossibleMoves(board);

    if (m_possibleCaptures.empty())
        SimpleMoves(board);
}

void BulltrickerPiece::SimpleMoves(const Board& board) {
    const auto white = GameConstants::BulltrickerConstants::WHITE;
    const auto black = GameConstants::BulltrickerConstants::BLACK;
    const auto& wPawnDir = GameConstants::BulltrickerConstants::WHITE_PAWN_DIR;
    const auto& bPawnDir = GameConstants::BulltrickerConstants::BLACK_PAWN_DIR;
    const auto& queenDir = GameConstants::BulltrickerConstants::QUEEN_DIR;

    std::vector<direction_t> const* directions;
    if (IsPawn()) {
        if (m_state.m_symbol == white)
            directions = &wPawnDir;
        else if (m_state.m_symbol == black)
            directions = &bPawnDir;
    }
    else if (IsQueen()) directions = &queenDir;
    else return;

    AddPossibleMoves(*directions, board);
}

void BulltrickerPiece::AddPossibleMoves(const std::vector<direction_t>& directions, const Board& board) {
    for (const auto& [dx, dy] : directions) {
        int x = GetX() + dx;
        int y = GetY() + dy;

        auto coord = std::make_pair(x, y);
        if (IsPawn() && IsWithinBoard(coord, board) && IsEmptyCell(coord, board)) {
            m_possibleMoves.push_back(coord);
        }
        
        else if (IsQueen()) {
            while (IsWithinBoard(coord, board) && IsEmptyCell(coord, board)) {
                m_possibleMoves.push_back(coord);

                if (dx == 1 || dx == -1 || dy == 1 || dy == -1) break; // Queen can move only one cell in diagonal

                x += dx;
                y += dy;
                coord = std::make_pair(x, y);
            }
        }
    }
}


void BulltrickerPiece::CaptureMoves(const Board& board) {
    if (m_state.m_type == BT_PieceType::BT_PAWN && !IsPromoted()) {
        int dx = (m_state.m_symbol == GameConstants::BulltrickerConstants::WHITE) ? -2 : 2; // White pawns move up (-1), black pawns move down (+1)
        int x = GetX() + dx;
        int y = GetY(); // y does not change because capture frontale
        const auto opponentCoord = std::make_pair(x, y);
        const auto landingCoord = std::make_pair(x + dx, y);

        if (IsWithinBoard(opponentCoord, board) && IsOpponentPiece(opponentCoord, board) && 
            IsWithinBoard(landingCoord, board) && IsEmptyCell(landingCoord, board)) {
           
            m_possibleMoves.push_back(landingCoord);
            m_possibleCaptures.emplace_back(dx, 0); 
        }
    }
}



bool BulltrickerPiece::IsOpponentPiece(const coord_t coord, const Board& board) const
{
    if (IsWithinBoard(coord, board)) 
    {
        const auto piece = board.GetPiece(coord);
        if (piece == nullptr) return false;
        const auto pieceColor = piece->GetSymbol();
        return pieceColor != m_state.m_symbol;
    }

    return false;
}


void BulltrickerPiece::Promote()
{
    m_state.m_type = BT_QUEEN;
}

void BulltrickerPiece::OrientationHorizontal()
{
    m_isHorizontal = true;
}

void BulltrickerPiece::OrientationVertical()
{
    m_isHorizontal = false;
}

// Helper functions to determine if the piece is a pawn or a queen
bool BulltrickerPiece::IsPawn() const {
    return m_state.m_type == BT_PAWN;
}

bool BulltrickerPiece::IsQueen() const {
    return m_state.m_type == BT_QUEEN;
}

bool BulltrickerPiece::IsPromoted() const
{
    return m_state.m_type == BT_QUEEN;
}

bool BulltrickerPiece::IsHorizontal() const
{
    return m_isHorizontal;
}