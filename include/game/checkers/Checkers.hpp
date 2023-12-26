#pragma once

#include "../../CheckersBoard.hpp"
#include "../../Player.hpp"
#include "../../Types.hpp"

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
    bool m_capturingMoveRequired = false;

    bool m_replay = false;

    void PieceIsSelected();
    void PieceIsNotSelected();
    void CurrentPlayerChanged();
    void SelectPieceChanged();
    void BoardNeedUpdate();
    void GameStarted();
    void GameFinished();

    void CapturingMoveRequired();
    
    void ResetPieceCapturedFlag();
    void ResetCapturingMoveRequiredFlag();
};

struct CheckersStatus {
    coord_t m_selectedPieceCoord = {-1, -1};
    coord_t m_lastSelectedPiece = {-1, -1};

    coord_t m_savedNewPosition = {-1, -1};

    std::vector<coord_t> m_currentPossibleMoves;
    std::vector<coord_t> m_lastPossibleMoves;
    char m_winner = CheckersConstants::NOWINNER; // -1 = no winner 0 = white, 1 = black

    void SaveLastPossibleMoves() 
    {
        m_lastPossibleMoves = m_currentPossibleMoves;
    }
    void SaveLastSelectedPiece()
    {
        m_lastSelectedPiece = m_selectedPieceCoord;
    }

    void SetSelectedPiece(coord_t coord)
    {
        m_selectedPieceCoord = coord;
    }
    void SetPossibleMoves(std::vector<coord_t> const& moves)
    {
        m_currentPossibleMoves = moves;
    }

    void ResetSelectedPiece()
    {
        m_selectedPieceCoord = {-1, -1};
    }
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

        bool IsPieceOfCurrentPlayer(coord_t coord) const;
        void CheckForWin();

        // piece
        void SelectPiece(coord_t coord);
        void DeselectPiece();
        bool IsMovePossible(coord_t coord) const;
        
        // move
        void PerformMove(coord_t coord);
        bool HasCapturingMoves(coord_t coord) const;
        bool IsCapturingMove(coord_t coord) const;
        void PerformCapturingMove(coord_t coord);
        void PerformNonCapturingMove(coord_t coord);
        bool HavePieceWithCapturingMoves() const;
        bool HavePieceWithNonCapturingMoves() const;

        bool CanPromotePiece(coord_t coord) const;
        void PromotePiece(coord_t coord);

        // Change the value of boolean flags
        bool AreCoordinatesValid(coord_t coord) const;
    public:
        Checkers();
        ~Checkers();

        // player
        void SwitchPlayer();

        // turn
        void Turn(coord_t coord);

        // initialization
        void Init();
    
        void GameStart();
        
        void ResetCurrentPlayerChangedFlag();
        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();

        CheckersPiece* GetPiece(coord_t coord) const;
        char GetWinner() const;

        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::vector<coord_t> GetPossibleMoves(coord_t coord) const;
        std::unique_ptr<CheckersBoard>& GetBoard();
        bool& IsGameStarted();
        bool& IsGameFinished();
        coord_t GetSelectedPiece() const;
        coord_t GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<coord_t> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;
};