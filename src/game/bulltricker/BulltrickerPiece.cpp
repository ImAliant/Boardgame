#include "../../../include/game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(const coord_t coord, const std::shared_ptr<Player> owner, 
                                   const char symbol, const int type, const bool isHorizontal):
    Piece{coord, owner, symbol}
{
    m_state.m_type = type;
    m_isHorizontal = isHorizontal;
}
BulltrickerPiece::~BulltrickerPiece(){}

void BulltrickerPiece::FindPossibleMoves(const Board& board)
{
    Piece::FindPossibleMoves(board);

    if (m_possibleCaptures.empty())
        SimpleMoves(board);
}

void BulltrickerPiece::SimpleMoves(const Board& board)
{
    //const auto& directions = ???

    /// AddPossibleMoves(directions, board); ???
}

void BulltrickerPiece::CaptureMoves(const Board& board)
{
    //const auto& directions = ???

    /// AddPossibleMoves(directions, board); ???
}

void BulltrickerPiece::Promote()
{
    m_state.m_type = BT_QUEEN;
}

bool BulltrickerPiece::IsPromoted() const
{
    return m_state.m_type == BT_QUEEN;
}

bool BulltrickerPiece::IsHorizontal() const
{
    return m_isHorizontal;
}