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
    
    void PieceIsSelected();
    void PieceIsNotSelected();
    void CurrentPlayerChanged();
    void SelectPieceChanged();
    void BoardNeedUpdate();
    
    //void ResetPieceCapturedFlag();
};

struct ButinStatus {
    std::pair<int, int> m_selectedPiece = {-1, -1};
    std::pair<int, int> m_lastSelectedPiece = {-1, -1};

    std::vector<std::pair<int, int>> m_currentPossibleMoves;
    std::vector<std::pair<int, int>> m_lastPossibleMoves;

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

      //  std::vector<std::pair<int, int>> GetPossibleMoves(int x, int y) const;
        //void UpdatePossibleMoves() const;

        void SelectPiece(std::pair<int, int> coord);
        void DeselectPiece();
        void SetSelectedPiece(const std::pair<int, int>& coords);


      //  bool IsPieceOfCurrentPlayer(std::pair<int, int> coord) const;
        //void CheckForWin();

        // piece
        //void SelectPiece(std::pair<int, int> coord);
        //void DeselectPiece();
        //bool IsMovePossible(std::pair<int, int> coord) const;
        //void ApplyMove(std::pair<int, int> coord);
        //bool CheckCapture(std::pair<int, int> coord);
        //void CapturePiece(std::pair<int, int> coord);
        //bool CanPromotePiece(std::pair<int, int> coord) const;
        //void PromotePiece(std::pair<int, int> coord);

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
        //void ResetCurrentPlayerChangedFlag();
        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();
        //std::pair<int, int> GetSelectedPiece() const;

        ButinPiece* GetPiece(std::pair<int, int> coord) const;

        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::vector<std::pair<int, int>> GetPossibleMoves(int x, int y) const;
        std::unique_ptr<ButinBoard>& GetBoard();
        bool& IsGameStarted();
        //bool& IsGameFinished();
        std::pair<int, int> GetSelectedPiece() const;
        std::pair<int, int> GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<std::pair<int, int>> GetLastPossibleMoves() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;
        void UpdatePossibleMoves() const;
};