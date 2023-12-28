#include "../../../include/game/butin/ButinFlags.hpp"

bool ButinFlags::IsFirstRound() const
{
    return m_isFirstRound;
}
/*bool ButinFlags::IsPieceMoved() const
{
    return m_pieceMoved;
}
void ButinFlags::PieceMoved()
{
    m_pieceMoved = true;
}
void ButinFlags::ResetPieceMovedFlag()
{
    m_pieceMoved = false;
}*/
void ButinFlags::EndFirstRound()
{
    m_isFirstRound = false;
}