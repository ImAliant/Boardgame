#pragma once

#include <memory>
#include <vector>

#include "../../Player.hpp"
#include "../../Types.hpp"
#include "../../Constants.hpp"

/**
 * @class CheckersStatus
 * @brief Classe contenant des informations sur l'état du jeu.
 */
class CheckersStatus
{
    private:
        /// @brief Joueur courant.
        std::shared_ptr<Player> m_currentPlayer;
        /// @brief Coordonnées de la pièce sélectionnée.
        coord_t m_selectedPieceCoord = {-1, -1};
        /// @brief Coordonnées de la dernière pièce sélectionnée.
        coord_t m_lastSelectedPiece = {-1, -1};
        /// @brief Vecteur contenant les coordonnées des mouvements possibles.
        std::vector<coord_t> m_currentPossibleMoves;
        /// @brief Vecteur contenant les coordonnées des mouvements possibles de la dernière pièce sélectionnée.
        std::vector<coord_t> m_lastPossibleMoves;
        /// @brief Représente le gagnant de la partie.
        /// @details -1 = pas de gagnant, 0 = blanc, 1 = noir
        char m_winner = GameConstants::CheckersConstants::NOWINNER;

    public:
        /// @brief Défini le joueur courant.
        /// @param player Joueur courant.
        void SetCurrentPlayer(std::shared_ptr<Player> player)
        {
            m_currentPlayer = player;
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
        /// @brief Défini le gagnant de la partie.
        /// @param winner Symbole du gagnant.
        void SetWinner(char winner)
        {
            m_winner = winner;
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
        
        /// @brief Remet par défaut les coordonnées de la pièce sélectionnée.
        void ResetSelectedPiece()
        {
            m_selectedPieceCoord = {-1, -1};
        }

        std::shared_ptr<Player> GetCurrentPlayer() const
        {
            return m_currentPlayer;
        }
        coord_t GetSelectedPiece() const
        {
            return m_selectedPieceCoord;
        }
        coord_t GetLastSelectedPiece() const
        {
            return m_lastSelectedPiece;
        }
        std::vector<coord_t> GetLastPossibleMoves() const
        {
            return m_lastPossibleMoves;
        }
        char GetWinner() const
        {
            return m_winner;
        }
};