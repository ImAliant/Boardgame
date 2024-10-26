#pragma once

#include <memory>
#include <vector>

#include "Piece.hpp"

enum State {
    NOT_STARTED,
    STARTED,
    FINISHED
};

class GameState {
    private:
        State state;
        std::shared_ptr<Piece> selectedPiece;

        std::vector<std::shared_ptr<Move>> movesToDisplay;

        void Init();
    public:
        explicit GameState();
        ~GameState() = default;

        void SelectPiece(const std::shared_ptr<Piece> piece);
        void DeselectPiece();

        void SetMovesToDisplay(const std::vector<std::shared_ptr<Move>> moves);
        void ClearCurrentMoves();

        void Start();
        void Stop();

        bool IsPieceSelected() const;

        State GetState() const;
        std::shared_ptr<Piece> GetSelectedPiece() const;
        std::vector<std::shared_ptr<Move>> GetMovesToDisplay() const;

        friend std::ostream& operator<<(std::ostream& os, const GameState& state);
};