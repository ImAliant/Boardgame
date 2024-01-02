#include "../../../include/game/bulltricker/BulltrickerPiece.hpp"

BulltrickerPiece::BulltrickerPiece(coord_t coord, const std::shared_ptr<Player> owner,char color, bool king, bool queen): 
    Piece{coord, owner,color, king, queen}
{
   
    if (king) 
        m_state.type = PieceType::KING;
    
    if (queen) 
        m_state.type = PieceType::QUEEN;
    
    else 
        m_state.type = PieceType::PAWN;
    

}