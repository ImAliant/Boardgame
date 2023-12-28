#include "../../include/game/ModelFlags.hpp"

void ModelFlags::GameStarted()
{
    m_isGameStarted = true;
}
void ModelFlags::GameFinished()
{
    m_isGameFinished = true;
}
void ModelFlags::PieceIsSelected()
{
    m_isPieceSelected = true;
}
void ModelFlags::PieceIsNotSelected()
{
    m_isPieceSelected = false;
}
void ModelFlags::CurrentPlayerChanged()
{
    m_currentPlayerChanged = true;
}
void ModelFlags::SelectPieceChanged()
{
    m_selectedPieceChanged = true;
}
void ModelFlags::BoardNeedUpdate()
{
    m_boardNeedUpdate = true;
}
void ModelFlags::PieceIsCaptured()
{
    m_isPieceCaptured = true;
}
void ModelFlags::NeedReplay()
{
    m_replay = true;
}
bool ModelFlags::IsGameStarted() const
{
    return m_isGameStarted;
}
bool ModelFlags::IsGameFinished() const
{
    return m_isGameFinished;
}
bool ModelFlags::IsPieceSelected() const
{
    return m_isPieceSelected;
}
bool ModelFlags::IsSelectedPieceChanged() const
{
    return m_selectedPieceChanged;
}
bool ModelFlags::IsBoardNeedUpdate() const
{
    return m_boardNeedUpdate;
}
bool ModelFlags::IsCurrentPlayerChanged() const
{
    return m_currentPlayerChanged;
}
bool ModelFlags::IsPieceCaptured() const
{
    return m_isPieceCaptured;
}
bool ModelFlags::IsReplay() const
{
    return m_replay;
}
void ModelFlags::ResetPieceCapturedFlag()
{
    m_isPieceCaptured = false;
}
void ModelFlags::ResetCurrentPlayerChangedFlag()
{
    m_currentPlayerChanged = false;
}
void ModelFlags::ResetSelectedPieceFlag()
{
    m_selectedPieceChanged = false;
}
void ModelFlags::ResetBoardNeedUpdateFlag()
{
    m_boardNeedUpdate = false;
}
void ModelFlags::ResetReplayFlag()
{
    m_replay = false;
}