#pragma once

#include "../GameStatus.hpp"

/**
 * @class ButinStatus 
 * @brief Classe contenant des informations sur l'état du jeu.
 */
class ButinStatus: public GameStatus
{
    private:
        /// @brief Représente le gagnant de la partie.
        Player* m_winner = nullptr;
        /// @brief Score du gagnant.
        int m_winnerScore = 0;

        int m_currentPlayerIndex = 0;
    public:
        void IncrementCurrentPlayerIndex()
        {
            m_currentPlayerIndex++;
        }

        /// @brief Défini le gagnant de la partie.
        /// @param winner Joueur gagnant.
        void SetWinner(Player* winner)
        {
            m_winner = winner;
        } 
        void SetWinnerScore(int score)
        {
            m_winnerScore = score;
        }
        void SetCurrentPlayerIndex(int index)
        {
            m_currentPlayerIndex = index;
        }

        Player* GetWinner() const
        {
            return m_winner;
        }
        int GetWinnerScore() const
        {
            return m_winnerScore;
        }
        int GetCurrentPlayerIndex() const
        {
            return m_currentPlayerIndex;
        }
};