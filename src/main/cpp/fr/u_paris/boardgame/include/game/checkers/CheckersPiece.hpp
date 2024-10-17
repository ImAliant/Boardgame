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

        void FindSimpleMoves(std::shared_ptr<Board> board) override;
        void FindJumpMoves(std::shared_ptr<Board> board) override;

        bool IsBlack() const;
        bool IsQueen() const;
    public:
        explicit CheckersPiece(const coord_t c, const char s);
        ~CheckersPiece() override = default;

        void Upgrade();

        PieceType GetType() const;
};