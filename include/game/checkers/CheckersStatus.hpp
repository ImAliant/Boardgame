#pragma once

#include "../GameStatus.hpp"

/**
 * @class CheckersStatus
 * @brief Classe contenant des informations sur l'état du jeu.
 */
class CheckersStatus: public GameStatus
{
    private:
        /// @brief Représente le gagnant de la partie.
        /// @details -1 = pas de gagnant, 0 = blanc, 1 = noir
        char m_winner = GameConstants::CheckersConstants::NOWINNER;
    public:
        /// @brief Défini le gagnant de la partie.
        /// @param winner Symbole du gagnant.
        void SetWinner(char winner)
        {
            m_winner = winner;
        }
        char GetWinner() const
        {
            return m_winner;
        }
};