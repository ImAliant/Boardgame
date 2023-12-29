#include "../../include/game/Model.hpp"

void Model::SwitchPlayer(GameStatus& m_status, ModelFlags& m_flags)
{
    m_status.SetCurrentPlayer(
        m_status.GetCurrentPlayer() == m_players[GameConstants::PLAYER_ONEID] ? 
            m_players[GameConstants::PLAYER_TWOID] : m_players[GameConstants::PLAYER_ONEID]
    );

    m_flags.ResetFlags();
    m_flags.CurrentPlayerChanged();
}