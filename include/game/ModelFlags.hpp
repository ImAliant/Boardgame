#pragma once

/**
 * @brief Classe contenant des indicateurs des modèles.
 * 
 */
class ModelFlags
{
    friend class Butin;
    friend class Checkers;

    protected:
        /// @brief Indique si la partie a commencée.
        bool m_isGameStarted = false;
        /// @brief Indique si la partie est finie.
        bool m_isGameFinished = false;
        /// @brief Indique si une pièce est sélectionnée.
        bool m_isPieceSelected = false;
        /// @brief Indique si la pièce sélectionnée a changée.
        bool m_selectedPieceChanged = false;
        /// @brief Indique si le plateau doit être mis à jour.
        bool m_boardNeedUpdate = false;
        /// @brief Indique si une pièce a été capturée.
        bool m_isPieceCaptured = false;
        /// @brief Indique si le joueur courant a changé.
        bool m_currentPlayerChanged = false;
        /// @brief Indique si le joueur doit continuer sont tour pour capturer une autre piece adverse.
        bool m_replay = false;
    
        /// @brief Défini l'indicateur \b m_isGameStarted à \b true
        void GameStarted();
        /// @brief Défini l'indicateur \b m_isGameFinished à \b true
        void GameFinished();
        /// @brief Défini l'indicateur \b m_isPieceSelected à \b true
        void PieceIsSelected();
        /// @brief Défini l'indicateur \b m_isPieceSelected à \b false
        void PieceIsNotSelected();
        /// @brief Défini l'indicateur \b m_currentPlayerChanged à \b true
        void CurrentPlayerChanged();
        /// @brief Défini l'indicateur \b m_selectedPieceChanged à \b true
        void SelectPieceChanged();
        /// @brief Défini l'indicateur \b m_boardNeedUpdate à \b true
        void BoardNeedUpdate();
        /// @brief Défini l'indicateur \b m_isPieceCaptured à \b true
        void PieceIsCaptured();
        /// @brief Défini l'indicateur \b m_replay à \b true
        void NeedReplay();

        /// @brief Remet par défaut l'indicateur \b m_isPieceCaptured
        void ResetPieceCapturedFlag();
        /// @brief Remet par défaut l'indicateur \b m_currentPlayerChanged
        void ResetCurrentPlayerChangedFlag();
        /// @brief Remet par défaut l'indicateur \b m_selectedPieceChanged
        void ResetSelectedPieceFlag();
        /// @brief Remet par défaut l'indicateur \b m_boardNeedUpdate
        void ResetBoardNeedUpdateFlag();
        /// @brief Remet par défaut l'indicateur \b m_replay
        void ResetReplayFlag();

        /// @brief Indique si la partie a commencée.
        bool IsGameStarted() const;
        /// @brief Indique si la partie est finie.
        bool IsGameFinished() const;
        /// @brief Indique si une pièce est sélectionnée.
        bool IsPieceSelected() const;
        /// @brief Indique si la pièce sélectionnée a changée.
        bool IsSelectedPieceChanged() const;
        /// @brief Indique si le plateau doit être mis à jour.
        bool IsBoardNeedUpdate() const;
        /// @brief Indique si le joueur courant a changé. 
        bool IsCurrentPlayerChanged() const;
        /// @brief Indique si une pièce a été capturée.
        bool IsPieceCaptured() const;
        /// @brief Indique si le joueur doit continuer sont tour pour capturer une autre piece adverse.
        bool IsReplay() const;
};