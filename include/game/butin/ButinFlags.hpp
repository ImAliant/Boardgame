#pragma once

#include "../ModelFlags.hpp"

/**
 * @brief Classe contenant des indicateurs du modèle du jeu de butin.
 * 
 */
class ButinFlags: public ModelFlags
{
    private:
        /// @brief Indique si il s'agit du tour de préparation.
        bool m_isFirstRound = true;
        /// @brief Indique si une pièce a été déplacée.
        //bool m_pieceMoved = false;
    public:
        /// @brief Indique si il s'agit du tour de préparation.
        bool IsFirstRound() const;
        /// @brief Indique si une pièce a été déplacée.
        //bool IsPieceMoved() const;

        /// @brief Défini l'indicateur \b m_pieceMoved à \b true
        //void PieceMoved();
        /// @brief Défini l'indicateur \b m_pieceMoved à \b false
        //void ResetPieceMovedFlag();
        /// @brief Défini l'indicateur \b m_isFirstRound à \b false
        void EndFirstRound();
};