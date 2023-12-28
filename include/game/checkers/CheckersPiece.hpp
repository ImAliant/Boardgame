#pragma once

#include "../../Piece.hpp"
#include "../../Constants.hpp"
#include "CheckersBoard.hpp"

class CheckersBoard;

enum PieceType
{
    EMPTY,
    PAWN,
    QUEEN
};

class CheckersPiece: public Piece
{
    private:
        bool IsWithinBoard(const CheckersBoard& board, coord_t coord) const;
        bool IsOpponentPiece(const CheckersBoard& board, coord_t coord) const;
        bool IsEmptyCell(const CheckersBoard& board, coord_t coord) const;
        
        void SimpleMoves(const CheckersBoard& board);
        void CaptureMoves(const CheckersBoard& board);
        void AddPossibleMoves(const CheckersBoard& board, std::vector<direction_t> const& directions);
        void QueenCaptureDirections(const CheckersBoard& board, direction_t direction);
    public:
        CheckersPiece() = default;
        CheckersPiece(coord_t coord, std::shared_ptr<Player> owner, char symbol);
        ~CheckersPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece);

        void FindPossibleMoves(const Board& board) override;

        void Promote();
        bool IsPromoted() const;

        std::string GetType() const;
};
