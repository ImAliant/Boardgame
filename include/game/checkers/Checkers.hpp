#pragma once

#include "../../CheckersBoard.hpp"
#include "../../Player.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

struct flagsmodel_t {
    bool m_isGameStarted = false;
    bool m_isGameFinished = false;
    bool m_isPieceSelected = false;
    bool m_selectedPieceChanged = false;
    bool m_boardNeedUpdate = false;
    bool m_isPieceCaptured = false;
    bool m_currentPlayerChanged = false;
};

struct CheckersStatus {
    std::pair<int, int> m_selectedPiece = {-1, -1};
    std::pair<int, int> m_lastSelectedPiece = {-1, -1};

    std::vector<std::pair<int, int>> m_currentPossibleMoves;
    std::vector<std::pair<int, int>> m_lastPossibleMoves;
};

class Checkers
{
    private:
        std::unique_ptr<CheckersBoard> m_board;
        std::vector<std::shared_ptr<Player>> m_players;
        std::shared_ptr<Player> m_currentPlayer;

        CheckersStatus m_status;

        flagsmodel_t m_flags;

        void InitBoard();
        void InitPlayers();

        void UpdatePossibleMoves() const;

        bool IsPieceOfCurrentPlayer(std::pair<int, int> coord) const;
        void CheckForWin();

        // piece
        void SelectPiece(std::pair<int, int> coord);
        void DeselectPiece();
        bool IsMovePossible(std::pair<int, int> coord) const;
        void ApplyMove(std::pair<int, int> coord);
        bool CheckCapture(std::pair<int, int> coord);
        void CapturePiece(std::pair<int, int> coord);
        bool CanPromotePiece(std::pair<int, int> coord) const;
        void PromotePiece(std::pair<int, int> coord);

        void SaveLastPossibleMoves();
        void SaveLastSelectedPiece();

        // Change the value of boolean flags
        void PieceIsSelected();
        void PieceIsNotSelected();
        void CurrentPlayerChanged();
        void SelectPieceChanged();
        void BoardNeedUpdate();

        void ResetPieceCapturedFlag();
        bool AreCoordinatesValid(std::pair<int, int> coord) const;

        void SetSelectedPiece(std::pair<int, int> coord);
    public:
        Checkers();
        ~Checkers();

        // player
        void SwitchPlayer();

        // turn
        void Turn(std::pair<int, int> coord);

        // initialization
        void Init();
    
        void GameStart();
        
        void ResetCurrentPlayerChangedFlag();
        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();

        CheckersPiece& GetPiece(std::pair<int, int> coord/*int x, int y*/) const;
        
        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::vector<std::pair<int, int>> GetPossibleMoves(int x, int y) const;
        std::unique_ptr<CheckersBoard>& GetBoard();
        bool& IsGameStarted();
        bool& IsGameFinished();
        std::pair<int, int> GetSelectedPiece() const;
        std::pair<int, int> GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<std::pair<int, int>> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;
};