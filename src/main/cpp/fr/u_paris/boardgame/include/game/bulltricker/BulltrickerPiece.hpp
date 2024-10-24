#pragma once

#include "../Piece.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::Bulltricker;

class BulltrickerPiece: public Piece
{
    private:
        Orientation orientation = HORIZONTAL;
        Color color = WHITE;
        PieceType type = PAWN;

        void FindMoves(std::shared_ptr<Board> board) override;

        void FindKingMoves(std::shared_ptr<Board> board);
        void FindQueenMoves(std::shared_ptr<Board> board);
        void FindPawnMoves(std::shared_ptr<Board> board);

        void HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board) override;
    public:
        explicit BulltrickerPiece(const coord_t c, const char s);
        ~BulltrickerPiece() override = default;

        void Upgrade();
        void SwitchOrientation();

        bool IsHorizontal() const;
        bool IsBlack() const;
        bool IsKing() const;
        bool IsQueen() const;
        bool IsPawn() const;

        Orientation GetOrientation() const;
        Color GetColor() const;
        PieceType GetType() const;

        void SetOrientation(const Orientation o);
        void SetColor(const Color c);
        void SetType(const PieceType t);
};