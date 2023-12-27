#pragma once

#include "ButinBoard.hpp"
#include "../../Player.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

struct Butin_flagsmodel_t {
    bool m_isGameStarted = false;
    bool m_isGameFinished = false;
    bool m_isPieceSelected = false;
    bool m_selectedPieceChanged = false;
    bool m_boardNeedUpdate = false;
    bool m_isPieceCaptured = false;
    bool m_currentPlayerChanged = false;
    bool m_isFirstRound = true;
    bool m_pieceMoved = false;

    void GameStarted();
    void GameFinished();
    void PieceIsSelected();
    void PieceIsNotSelected();
    void CurrentPlayerChanged();
    void SelectPieceChanged();
    void BoardNeedUpdate();
    void PieceMoved();
};

struct ButinStatus {
    std::shared_ptr<Player> m_currentPlayer;
    coord_t m_selectedPiece = {-1, -1};
    coord_t m_lastSelectedPiece = {-1, -1};

    int m_currentPlayerIndex = 1;

    std::vector<coord_t> m_currentPossibleMoves;
    std::vector<coord_t> m_lastPossibleMoves;

    Player* m_winner = nullptr;
    int m_winnerScore = 0;

    void SaveLastPossibleMoves() 
    {
        m_lastPossibleMoves = m_currentPossibleMoves;
    }
    void SaveLastSelectedPiece()
    {
        m_lastSelectedPiece = m_selectedPiece;
    }
    void SetCurrentPlayer(std::shared_ptr<Player> player)
    {
        m_currentPlayer = player;
    }
};

class Butin
{
    private:
        std::unique_ptr<ButinBoard> m_board;
        std::vector<std::shared_ptr<Player>> m_players;
        
        ButinStatus m_status;

        Butin_flagsmodel_t m_flags;

        void InitBoard();
        void InitPlayers();
       
        void HandleFirstRoundSelection(coord_t coord);

        void SelectPiece(coord_t coord);
        void DeselectPiece();
        void SetSelectedPiece(coord_t coord);
       
        bool IsMovePossible(coord_t coord) const;
        void PerformMove(coord_t coord);
      
        void UpdatePossibleMoves() const;
        void UpdatePlayerScore(char pieceType);
        bool CheckForWinner() const;

        // Change the value of boolean flags
        bool AreCoordinatesValid(coord_t coord) const;
    public:
        Butin();
        ~Butin();

        // player
        void SwitchPlayer();

        // turn
        void Turn(coord_t coord);

        // initialization
        void Init();
    
        void GameStart();

        bool IsFirstRound() const;
        void EndFirstRound();
        void EndFirstRoundIfNeeded();
        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();
        bool& IsGameStarted();
        bool& IsGameFinished();

        Player* DetermineWinner();
        
        ButinPiece* GetPiece(coord_t coord) const;
        bool hasPieceMoved() const;
        
        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::vector<coord_t> GetPossibleMoves(coord_t coord) const;
        std::unique_ptr<ButinBoard>& GetBoard();
        coord_t GetSelectedPiece() const;
        coord_t GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<coord_t> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;
        Player* GetWinner() const;
        void setWinner(Player* winner);
        void setWinnerScore(int score);
        int getWinnerScore() const;
};