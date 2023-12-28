#include "../../../include/game/checkers/CheckersFlags.hpp"

void CheckersFlags::GameStarted()
{
    m_isGameStarted = true;
}
void CheckersFlags::GameFinished()
{
    m_isGameFinished = true;
}
void CheckersFlags::PieceIsSelected()
{
    m_isPieceSelected = true;
}
void CheckersFlags::PieceIsNotSelected()
{
    m_isPieceSelected = false;
}
void CheckersFlags::CurrentPlayerChanged()
{
    m_currentPlayerChanged = true;
}
void CheckersFlags::SelectPieceChanged()
{
    m_selectedPieceChanged = true;
}
void CheckersFlags::BoardNeedUpdate()
{
    m_boardNeedUpdate = true;
}
void CheckersFlags::CapturingMoveRequired()
{
    m_capturingMoveRequired = true;
}
void CheckersFlags::NeedReplay()
{
    m_replay = true;
}
void CheckersFlags::PieceIsCaptured()
{
    m_isPieceCaptured = true;
}

void CheckersFlags::ResetPieceCapturedFlag()
{
    m_isPieceCaptured = false;
}
void CheckersFlags::ResetCapturingMoveRequiredFlag()
{
    m_capturingMoveRequired = false;
}
void CheckersFlags::ResetCurrentPlayerChangedFlag()
{
    m_currentPlayerChanged = false;
}
void CheckersFlags::ResetSelectedPieceFlag()
{
    m_selectedPieceChanged = false;
}
void CheckersFlags::ResetBoardNeedUpdateFlag()
{
    m_boardNeedUpdate = false;
}
void CheckersFlags::ResetReplayFlag()
{
    m_replay = false;
}

void CheckersFlags::SetCapturingMoveRequiredFlag(bool value)
{
    m_capturingMoveRequired = value;
}

bool CheckersFlags::IsGameStarted() const
{
    return m_isGameStarted;
}
bool CheckersFlags::IsGameFinished() const
{
    return m_isGameFinished;
}
bool CheckersFlags::IsPieceSelected() const
{
    return m_isPieceSelected;
}
bool CheckersFlags::IsSelectedPieceChanged() const
{
    return m_selectedPieceChanged;
}
bool CheckersFlags::IsBoardNeedUpdate() const
{
    return m_boardNeedUpdate;
}
bool CheckersFlags::IsCurrentPlayerChanged() const
{
    return m_currentPlayerChanged;
}
bool CheckersFlags::IsCapturingMoveRequired() const
{
    return m_capturingMoveRequired;
}
bool CheckersFlags::IsReplay() const
{
    return m_replay;
}
bool CheckersFlags::IsPieceCaptured() const
{
    return m_isPieceCaptured;
}