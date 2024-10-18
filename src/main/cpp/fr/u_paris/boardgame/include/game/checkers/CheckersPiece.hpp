#pragma once

#include "../Piece.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::Checkers;

class CheckersPiece: public Piece
{
    private:
        PieceType type = PAWN;

        void FindMoves(std::shared_ptr<Board> board) override;
        void FindQueenMoves(std::shared_ptr<Board> board);

        void AddPossibleMoveForEmptySpace(const coord_t& to);
        void HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board) override;

        bool IsBlack() const;
        bool IsQueen() const;
    public:
        explicit CheckersPiece(const coord_t c, const char s);
        ~CheckersPiece() override = default;

        void Upgrade();

        PieceType GetType() const;
};