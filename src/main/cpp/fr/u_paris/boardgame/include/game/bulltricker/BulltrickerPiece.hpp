#pragma once

#include "../Piece.hpp"

class BulltrickerPiece: public Piece
{
    private:
        bool is_horizontal = false;
        bool is_black = false;

        void FindSimpleMoves(std::shared_ptr<Board> board) override;
        void FindJumpMoves(std::shared_ptr<Board> board) override;
    public:
        explicit BulltrickerPiece(const coord_t c, const char s);
        ~BulltrickerPiece() override = default;

        bool IsHorizontal() const;
        bool IsBlack() const;

        void SetHorizontal(const bool h);
        void SetBlack(const bool b);
};