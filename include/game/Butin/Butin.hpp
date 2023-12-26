#pragma once

#include "../../ButinBoard.hpp"
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
    bool isFirstRound = true;
    bool m_PieceMoved = false;
    
    void PieceMoved();
    void PieceIsSelected();
    void PieceIsNotSelected();
    void CurrentPlayerChanged();
    void SelectPieceChanged();
    void BoardNeedUpdate();
    void GameFinished();
    
    
};

struct ButinStatus {
    std::pair<int, int> m_selectedPiece = {-1, -1};
    std::pair<int, int> m_lastSelectedPiece = {-1, -1};

    std::vector<std::pair<int, int>> m_currentPossibleMoves;
    std::vector<std::pair<int, int>> m_lastPossibleMoves;

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


};
class Butin
{
    private:
        std::unique_ptr<ButinBoard> m_board;
        std::vector<std::shared_ptr<Player>> m_players;
        std::shared_ptr<Player> m_currentPlayer;
        int m_currentPlayerIndex = 1;
        ButinStatus m_status;

        Butin_flagsmodel_t m_flags;

        void InitBoard();
        void InitPlayers();
       
        void HandleFirstRoundSelection(const std::pair<int, int>& coords);

     
        void SelectPiece(std::pair<int, int> coord);
        void DeselectPiece();
        void SetSelectedPiece(const std::pair<int, int>& coords);
       
        bool IsMovePossible(std::pair<int, int> coord) const;
        void ApplyMove(std::pair<int, int> coord);
      

        // Change the value of boolean flags
        bool AreCoordinatesValid(std::pair<int, int> coord) const;

        
    public:
        Butin();
        ~Butin();

        // player
        void SwitchPlayer();

        // turn
        void Turn(std::pair<int, int> coord);

        // initialization
        void Init();
    
        void GameStart();
         bool IsFirstRound() const;
        void EndFirstRound();
        void EndFirstRoundIfNeeded();
        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();
        

        ButinPiece* GetPiece(std::pair<int, int> coord) const;
        bool hasPieceMoved() const ;
        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::vector<std::pair<int, int>> GetPossibleMoves(int x, int y) const;
        std::unique_ptr<ButinBoard>& GetBoard();
        bool& IsGameStarted();
        bool& IsGameFinished();
        std::pair<int, int> GetSelectedPiece() const;
        std::pair<int, int> GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<std::pair<int, int>> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;
        void UpdatePossibleMoves() const;
        void UpdatePlayerScore(char pieceType);
        bool CheckForWinner() const;
        Player* GetWinner() const;
        void setWinner(Player* winner);
        void setWinnerScore(int score);
        int getWinnerScore() const;
        Player* DetermineWinner() ;
};