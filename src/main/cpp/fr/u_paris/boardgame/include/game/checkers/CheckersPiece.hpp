#pragma once

#include "../Piece.hpp"

enum PieceType
{
    PAWN,
    QUEEN
};

class CheckersPiece: public Piece
{
    private:
        PieceType type = PAWN;

        void FindMoves(std::shared_ptr<Board> board) override;

        void AddPossibleMoveForEmptySpace(const coord_t& from, const coord_t& to);
        void HandlePieceEncounter(const coord_t& from, const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board);

        bool IsBlack() const;
        bool IsQueen() const;
    public:
        explicit CheckersPiece(const coord_t c, const char s);
        ~CheckersPiece() override = default;

        void Upgrade();

        PieceType GetType() const;
};