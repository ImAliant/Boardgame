#pragma once

#include "CheckersBoard.hpp"
#include "CheckersStatus.hpp"
#include "CheckersFlags.hpp"
#include "../../Player.hpp"
#include "../../Types.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

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
        CheckersFlags m_flags;

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
        /// @brief Compte les pièces restantes de chaque joueur.
        /// @param whitePieces Nombre de pièces blanches.
        /// @param blackPieces Nombre de pièces noires.
        void CountPieces(int& whitePieces, int& blackPieces) const;
        /// @brief Termine la partie si un joueur n'a plus de pièces.
        /// @param whitePieces Nombre de pièces blanches.
        /// @param blackPieces Nombre de pièces noires.
        void EndGameIfNoPieces(int whitePieces, int blackPieces);
        /// @brief Termine la partie si un joueur n'a plus de mouvements possibles.
        void EndGameIfNoMoves();


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
        
        bool IsGameStarted() const;
        bool IsGameFinished() const;
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