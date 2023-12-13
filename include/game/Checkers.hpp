#pragma once

#include "../Board.hpp"
#include "../Player.hpp"

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Checkers
{
    private:
        std::unique_ptr<Board> m_board;
        std::vector<std::shared_ptr<Player>> m_players;
        std::shared_ptr<Player> m_currentPlayer;

        std::pair<int, int> m_lastSelectedPiece = {-1, -1};
        std::pair<int, int> m_selectedPiece = {-1, -1};

        std::vector<std::pair<int, int>> m_lastPossibleMoves;

        bool m_isGameStarted = false;
        bool m_isGameFinished = false;

        bool m_isPieceSelected = false;
        bool m_selectedPieceChanged = false;
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
        void CapturePiece(int x, int y);
        void RemovePiece(int x, int y);

        // initialization
        void InitBoard();
        void InitPlayers();

        void UpdatePossibleMoves() const;

        void GameStart();
        void ResetSelectedPieceFlag();
        bool AreCoordinatesValid(std::pair<int, int> coord) const;
        // getters
        std::shared_ptr<Player> GetCurrentPlayer() const;
        std::shared_ptr<Player> GetPlayer(Players player) const;
        Piece& GetPiece(int x, int y) const;
        std::vector<std::pair<int, int>> GetPossibleMoves(int x, int y) const;
        //std::vector<std::pair<int, int>> GetPossibleCaptures(int x, int y) const;
        std::unique_ptr<Board>& GetBoard();
        bool& IsGameStarted();
        bool& IsGameFinished();
        std::pair<int, int> GetSelectedPiece() const;
        std::pair<int, int> GetLastSelectedPiece() const;
        bool IsPieceSelected() const;
        bool IsSelectedPieceChanged() const;
        std::vector<std::pair<int, int>> GetLastPossibleMoves() const;
};