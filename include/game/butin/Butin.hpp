#pragma once

#include "ButinBoard.hpp"
#include "ButinStatus.hpp"
#include "ButinFlags.hpp"
#include "../../Player.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Butin
{
    private:
        std::unique_ptr<ButinBoard> m_board;
        std::vector<std::shared_ptr<Player>> m_players;

        ButinStatus m_status;
        ButinFlags m_flags;

        void InitBoard();
        void InitPlayers();

        void HandleFirstRoundSelection(const coord_t coord);
        bool IsYellowPiece(const coord_t coord) const;

        void SelectPiece(const coord_t coord);
        void DeselectPiece();

        bool IsMovePossible(const coord_t coord) const;
        void PerformMove(const coord_t coord);
        bool HasCapturingMoves(const coord_t coord) const;

        void UpdatePlayerScore(const char pieceType) const;
        void UpdatePossibleMoves() const;

        void EndFirstRoundIfNeeded();

        void CheckForWin();
        void DetermineWinner();

        bool AreCoordinatesValid(const coord_t coord) const;
    public:
        Butin();
        ~Butin();

        void SwitchPlayer();

        void Turn(coord_t coord);

        void Init();        

        void GameStart();
        void EndFirstRound();

        bool IsFirstRound() const;
        bool IsGameStarted() const;
        bool IsGameFinished() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        bool IsBoardNeedUpdate() const;
        bool IsCurrentPlayerChanged() const;

        void ResetSelectedPieceFlag();
        void ResetBoardNeedUpdateFlag();
        void ResetCurrentPlayerChangedFlag();

        ButinPiece* GetPiece(coord_t coord) const;
        std::unique_ptr<ButinBoard>& GetBoard();
        coord_t GetSelectedPiece() const;
        coord_t GetLastSelectedPiece() const;
        std::vector<coord_t> GetPossibleMoves(coord_t coord) const;
        std::vector<coord_t> GetLastPossibleMoves() const;
        std::shared_ptr<Player> GetCurrentPlayer() const;
        Player* GetWinner() const;
        int GetWinnerScore() const;
};