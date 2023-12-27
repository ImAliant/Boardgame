/**
 * @file Checkers.hpp
 * @author diamant alexandre / hamdi yahya
 * @brief 
 * @date 
 */

#pragma once

#include "CheckersBoard.hpp"
#include "../../Player.hpp"
#include "../../Types.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

/** 
 * @struct flagsmodel_t
 * @brief Structure contenant des indicateurs du modèle.
 * @details
 * Cette structure contient des indicateurs représentants divers état et évenement du jeu.
 * Les indicateurs sont initialisés à 'false'.
 */
struct flagsmodel_t {
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
    /// @brief Indique si un mouvement de capture est requis.
    bool m_capturingMoveRequired = false;
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
    /// @brief Défini l'indicateur \b m_capturingMoveRequired à \b true
    void CapturingMoveRequired();
    /// @brief Remet par défaut l'indicateur \b m_isPieceCaptured
    void ResetPieceCapturedFlag();
    /// @brief Remet par défaut l'indicateur \b m_capturingMoveRequired
    void ResetCapturingMoveRequiredFlag();
};

/**
 * @struct CheckersStatus
 * @brief Structure contenant des informations sur l'état du jeu.
 */
struct CheckersStatus {
    /// @brief Joueur courant.
    std::shared_ptr<Player> m_currentPlayer;
    /// @brief Coordonnées de la pièce sélectionnée.
    coord_t m_selectedPieceCoord = {-1, -1};
    /// @brief Coordonnées de la dernière pièce sélectionnée.
    coord_t m_lastSelectedPiece = {-1, -1};
    /// @brief Coordonnées de la nouvelle position après un mouvement de la dernière pièce sélectionnée.
    coord_t m_savedNewPosition = {-1, -1};
    /// @brief Vecteur contenant les coordonnées des mouvements possibles.
    std::vector<coord_t> m_currentPossibleMoves;
    /// @brief Vecteur contenant les coordonnées des mouvements possibles de la dernière pièce sélectionnée.
    std::vector<coord_t> m_lastPossibleMoves;
    /// @brief Représente le gagnant de la partie.
    /// @details -1 = pas de gagnant, 0 = blanc, 1 = noir
    char m_winner = GameConstants::CheckersConstants::NOWINNER;

    /// @brief Défini le joueur courant.
    /// @param player Joueur courant.
    void SetCurrentPlayer(std::shared_ptr<Player> player)
    {
        m_currentPlayer = player;
    }
    /// @brief Sauvegarde les coordonnées des mouvements possibles de la dernière pièce sélectionnée.
    void SaveLastPossibleMoves() 
    {
        m_lastPossibleMoves = m_currentPossibleMoves;
    }
    /// @brief Sauvegarde les coordonnées de la dernière pièce sélectionnée.
    void SaveLastSelectedPiece()
    {
        m_lastSelectedPiece = m_selectedPieceCoord;
    }
    /// @brief Défini les coordonnées de la pièce sélectionnée.
    /// @param coord Coordonnées de la pièce sélectionnée.
    void SetSelectedPiece(coord_t coord)
    {
        m_selectedPieceCoord = coord;
    }
    /// @brief Défini les mouvements possibles courants.
    /// @param moves Vecteur contenant les coordonnées des mouvements possibles.
    void SetPossibleMoves(std::vector<coord_t> const& moves)
    {
        m_currentPossibleMoves = moves;
    }
    /// @brief Remet par défaut les coordonnées de la pièce sélectionnée.
    void ResetSelectedPiece()
    {
        m_selectedPieceCoord = {-1, -1};
    }
};

/**
 * @class Checkers
 * @brief Classe représentant le modèle du jeu de dames.
 */
class Checkers
{
    private:
        /// @brief Plateau de jeu.
        std::unique_ptr<CheckersBoard> m_board;
        /// @brief Vecteur contenant les joueurs.
        std::vector<std::shared_ptr<Player>> m_players;
        /// @brief Etat du jeu.
        CheckersStatus m_status;

        /// @brief Indicateurs du modèle.
        flagsmodel_t m_flags;

        /// @brief Initialise le plateau de jeu.
        void InitBoard();
        /// @brief Initialise les joueurs.
        void InitPlayers();

        /// @brief Met à jour les mouvements possibles.
        void UpdatePossibleMoves() const;

        /// @brief Vérifie si la pièce sélectionnée est de la couleur du joueur courant.
        /// @param coord Coordonnées de la pièce.
        /// @return \b true si la pièce est de la couleur du joueur courant, \b false sinon.
        bool IsPieceOfCurrentPlayer(coord_t coord) const;
        /// @brief Permet de savoir si le joueur courant a gagné.
        void CheckForWin();

        /// @brief Sélectionne une pièce sur le plateau.
        /// @param coord Coordonnées de la pièce.
        void SelectPiece(coord_t coord);
        /// @brief Désélectionne la pièce sélectionnée.
        void DeselectPiece();
        /// @brief Vérifie si le mouvement est possible.
        /// @param coord Coordonnées de la destination.
        /// @return \b true si le mouvement est possible, \b false sinon.
        bool IsMovePossible(coord_t coord) const;
        
        /// @brief Effectue le mouvement d'une pièce.
        /// @param coord Coordonnées de la destination.
        void PerformMove(coord_t coord);
        /// @brief Vérifie si la pièce sélectionnée peut capturer une autre pièce.
        /// @param coord Coordonnées de la pièce.
        /// @return \b true si la pièce peut capturer une autre pièce, \b false sinon.
        bool HasCapturingMoves(coord_t coord) const;
        /// @brief Vérifie si la coordonnée est un mouvement de capture.
        /// @param coord Coordonnées de la destination.
        /// @return \b true si la coordonnée est un mouvement de capture, \b false sinon.
        bool IsCapturingMove(coord_t coord) const;
        /// @brief Effectue le mouvement de capture d'une pièce.
        /// @param coord Coordonnées de la destination.
        void PerformCapturingMove(coord_t coord);
        /// @brief Effectue le mouvement d'une pièce sans capture.
        /// @param coord Coordonnées de la destination.
        void PerformNonCapturingMove(coord_t coord);
        /// @brief Vérifie si une pièce du joueur courant peut capturer une autre pièce.
        /// @return \b true si une pièce du joueur courant peut capturer une autre pièce, \b false sinon.
        bool HavePieceWithCapturingMoves() const;
        /// @brief Vérifie si une pièce du joueur courant peut effectuer un mouvement sans capture.
        /// @return \b true si une pièce du joueur courant peut effectuer un mouvement sans capture, \b false sinon.
        bool HavePieceWithNonCapturingMoves() const;

        /// @brief Vérifie si la pièce sélectionnée peut être promue.
        /// @param coord Coordonnées de la pièce.
        bool CanPromotePiece(coord_t coord) const;
        /// @brief Promouvoit une pièce.
        /// @param coord Coordonnées de la pièce.
        void PromotePiece(coord_t coord);

        /// @brief Vérifie si les coordonnées sont bien dans le plateau.
        /// @param coord Coordonnées.
        /// @return \b true si les coordonnées sont dans le plateau, \b false sinon.
        bool AreCoordinatesValid(coord_t coord) const;
    public:
        Checkers();
        ~Checkers();

        void SwitchPlayer();

        // turn
        void Turn(coord_t coord);

        // initialization
        void Init();
    
        void GameStart();
        
        bool& IsGameStarted();
        bool& IsGameFinished();
        void ResetCurrentPlayerChangedFlag();
        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();

        CheckersPiece* GetPiece(coord_t coord) const;
        char GetWinner() const;

        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::vector<coord_t> GetPossibleMoves(coord_t coord) const;
        std::unique_ptr<CheckersBoard>& GetBoard();
        
        coord_t GetSelectedPiece() const;
        coord_t GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<coord_t> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;
};