#include "../../../include/game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(coord_t coord, const std::shared_ptr<Player> owner,char color, bool king, bool queen,bool isHorizontal): 
    Piece{coord, owner,color, king, queen},m_isHorizontal(isHorizontal)
{
   
    if (king) 
        m_state.type = BullT_PieceType::KING;
    
    if (queen) 
        m_state.type = BullT_PieceType::BT_QUEEN;
    
    else 
        m_state.type = BullT_PieceType::BT_PAWN;
    

}


BullT_PieceType BulltrickerPiece::GetType() const {
   
    return static_cast<BullT_PieceType>(m_state.type);
}

bool BulltrickerPiece::IsHorizontal() const {
   
    return m_isHorizontal;
}



void BulltrickerPiece::Promote()
{
    m_state.type = BullT_PieceType::BT_QUEEN;
}

bool BulltrickerPiece::IsPromoted() const
{
    return m_state.type == BullT_PieceType::BT_QUEEN;
}

std::ostream& operator<<(std::ostream& os, const BulltrickerPiece& piece)
{
    os << piece.m_state.m_symbol;

    return os;
}