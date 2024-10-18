#pragma once

#include "../Piece.hpp"

class ButinPiece: public Piece
{
    private: 
        void FindMoves(std::shared_ptr<Board> board) override;
        void HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board) override;
    public:
        explicit ButinPiece(const coord_t c, const char s);
        ~ButinPiece() override = default;

        bool IsBlack() const;
        bool IsRed() const;
        bool IsYellow() const;
};