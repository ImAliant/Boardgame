#pragma once

#include "../GameStatus.hpp"
#include "BulltrickerFlags.hpp"
#include "../Model.hpp"

class Bulltricker: public Model
{
    private:
        GameStatus m_status;
        BulltrickerFlags m_flags;

        void SelectPiece(const coord_t coord) override;
        void DeselectPiece() override;

        bool IsMovePossible(const coord_t coord) const override;
        void PerformMove(const coord_t coord) override;
        void ProcessConditionalMove(const coord_t coord) override;
        void ApplyCapture(const coord_t coord) override;
        void HandlePieceCaptureAndReplay(const coord_t coord) override;

        void InitPlayers() override;

        void SwitchPlayer() override;

        void CheckForWin() override;

        void CreateGameBoard() override;
        void CheckBoardDimensions(const int row, const int col) const override;
    public:
        ~Bulltricker() override = default;

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

        Player* GetWinner() const override;

        std::shared_ptr<Player> GetCurrentPlayer() const override;
        coord_t GetSelectedPiece() const override;
        coord_t GetLastSelectedPiece() const override;
        std::vector<coord_t> GetLastPossibleMoves() const override;
};