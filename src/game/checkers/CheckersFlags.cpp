#include "../../../include/game/checkers/CheckersFlags.hpp"

void CheckersFlags::CapturingMoveRequired()
{
    m_capturingMoveRequired = true;
}
/*void CheckersFlags::NeedReplay()
{
    m_replay = true;
}*/
void CheckersFlags::ResetCapturingMoveRequiredFlag()
{
    m_capturingMoveRequired = false;
}
/*void CheckersFlags::ResetReplayFlag()
{
    m_replay = false;
}*/
void CheckersFlags::SetCapturingMoveRequiredFlag(bool value)
{
    m_capturingMoveRequired = value;
}
bool CheckersFlags::IsCapturingMoveRequired() const
{
    return m_capturingMoveRequired;
}
/*bool CheckersFlags::IsReplay() const
{
    return m_replay;
}*/
