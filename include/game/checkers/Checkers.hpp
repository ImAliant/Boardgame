#pragma once

#include "CheckersBoard.hpp"
#include "CheckersStatus.hpp"
#include "CheckersFlags.hpp"
#include "../../Player.hpp"
#include "../../Types.hpp"

#include "../Model.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

/**
 * @class Checkers
 * @brief Classe représentant le modèle du jeu de dames.
 */
class Checkers: public Model
{
    private:
        /// @brief Etat du jeu.
        CheckersStatus m_status;
        /// @brief Indicateurs du modèle.
        CheckersFlags m_flags;
    
        /// @brief Sélectionne une pièce sur le plateau.
        /// @param coord Coordonnées de la pièce.
        void SelectPiece(const coord_t coord) override;
        /// @brief Désélectionne la pièce sélectionnée.
        void DeselectPiece() override;

        /// @brief Vérifie si la pièce sélectionnée est de la couleur du joueur courant.
        /// @param coord Coordonnées de la pièce.
        /// @return \b true si la pièce est de la couleur du joueur courant, \b false sinon.
        bool IsPieceOfCurrentPlayer(coord_t coord) const;

        /// @brief Vérifie si le mouvement est possible.
        /// @param coord Coordonnées de la destination.
        /// @return \b true si le mouvement est possible, \b false sinon.
        bool IsMovePossible(const coord_t coord) const override;
        /// @brief Effectue le mouvement d'une pièce.
        /// @param coord Coordonnées de la destination
        void PerformMove(const coord_t coord) override;
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
        
        void ProcessConditionalMove(const coord_t coord) override;
        void ApplyCapture(const coord_t coord) override;
        void HandlePieceCaptureAndReplay(const coord_t coord) override;

        void InitPlayers() override;

        /// @brief Vérifie si une pièce du joueur courant peut effectuer un mouvement.
        /// @param capturing Vérifie si le mouvement est une capture.
        bool HavePieceWithMoves(bool capturing) const;
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

        /// @brief Vérifie si le joueur courant a gagné.
        void CheckForWin() override;
        /// @brief Compte les pièces restantes de chaque joueur.
        /// @param whitePieces Nombre de pièces blanches.
        /// @param blackPieces Nombre de pièces noires.
        void CountPieces(int& whitePieces, int& blackPieces) const;
        /// @brief Termine la partie si un joueur n'a plus de pièces.
        /// @param whitePieces Nombre de pièces blanches.
        /// @param blackPieces Nombre de pièces noires.
        void EndGameIfNoPieces(int whitePieces, int blackPieces);
        /// @brief Termine la partie si un joueur n'a plus de mouvements possibles.
        void EndGameIfNoMoves() override;

        void CreateGameBoard() override;
        void CheckBoardDimensions(const int row, const int col) const override;
    public:
        ~Checkers() override = default;

        void Turn(const coord_t coord) override;

        void GameStart() override;
        
        bool IsGameStarted() const override;
        bool IsGameFinished() const override;
        bool IsPieceSelected() const override;
        bool IsSelectedPieceChanged() const override;
        bool IsBoardNeedUpdate() const override;
        bool IsCurrentPlayerChanged() const override;

        void ResetCurrentPlayerChangedFlag() override;
        void ResetSelectedPieceFlag() override;
        void ResetBoardNeedUpdateFlag() override;

        char GetWinner() const;

        std::shared_ptr<Player> GetCurrentPlayer() const override;
        coord_t GetSelectedPiece() const override;
        coord_t GetLastSelectedPiece() const override;
        std::vector<coord_t> GetLastPossibleMoves() const override;
};