#pragma once

#include "../ModelFlags.hpp"

/**
 * @brief Classe contenant des indicateurs du modèle du jeu de dames.
 * 
 */
class CheckersFlags: public ModelFlags
{
    private:
        /// @brief Indique si un mouvement de capture est requis.
        bool m_capturingMoveRequired = false;
        /// @brief Indique si le joueur doit continuer sont tour pour capturer une autre piece adverse.
        //bool m_replay = false;
    public:
        /// @brief Défini l'indicateur \b m_capturingMoveRequired à \b true
        void CapturingMoveRequired();
        /// @brief Défini l'indicateur \b m_replay à \b true
        //void NeedReplay();
        
        /// @brief Remet par défaut l'indicateur \b m_capturingMoveRequired
        void ResetCapturingMoveRequiredFlag();
        /// @brief Remet par défaut l'indicateur \b m_replay
        //void ResetReplayFlag();

        /// @brief Défini l'indicateur \b m_isGameStarted à \b value
        /// @param value Valeur à définir
        void SetCapturingMoveRequiredFlag(bool value);

        /// @brief Indique si un mouvement de capture est requis.
        bool IsCapturingMoveRequired() const;
        /// @brief Indique si le joueur doit continuer sont tour pour capturer une autre piece adverse.
        //bool IsReplay() const;
};