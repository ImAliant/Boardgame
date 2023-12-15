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
};

class Checkers
{
    private:
        std::unique_ptr<CheckersBoard> m_board;
        std::vector<std::shared_ptr<Player>> m_players;
        std::shared_ptr<Player> m_currentPlayer;

        std::pair<int, int> m_lastSelectedPiece = {-1, -1};
        std::pair<int, int> m_selectedPiece = {-1, -1};

        std::vector<std::pair<int, int>> m_lastPossibleMoves;

        flagsmodel_t m_flags;

        void ResetPieceCapturedFlag();
        bool AreCoordinatesValid(std::pair<int, int> coord) const;
    public:
        Checkers();
        ~Checkers();

        // player
        void SwitchPlayer();

        // turn
        void Turn(std::pair<int, int> coord);
        bool IsPieceOfCurrentPlayer(std::pair<int, int> coord) const;
        void CheckForWin();

        // piece
        void SelectPiece(std::pair<int, int> coord);
        void DeselectPiece();
        bool IsMovePossible(std::pair<int, int> coord) const;
        void ApplyMove(std::pair<int, int> coord);
        void PromotePiece(/**/);
        bool CheckCapture(std::pair<int, int> coord);
        void CapturePiece(int x, int y);
        bool IsPromoted(int x, int y) const;
        bool CanPromotePiece(std::pair<int, int> coord) const;

        // initialization
        void InitBoard();
        void InitPlayers();

        void UpdatePossibleMoves() const;

        void GameStart();

        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();

        CheckersPiece& GetPiece(int x, int y) const;
        
        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::shared_ptr<Player> GetPlayer(Players player) const;
        std::vector<std::pair<int, int>> GetPossibleMoves(int x, int y) const;
        std::vector<std::pair<int, int>> GetPossibleCaptures(int x, int y) const;
        std::unique_ptr<CheckersBoard>& GetBoard();
        bool& IsGameStarted();
        bool& IsGameFinished();
        std::pair<int, int> GetSelectedPiece() const;
        std::pair<int, int> GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<std::pair<int, int>> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
};