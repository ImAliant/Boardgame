#pragma once

#include "Piece.hpp"
#include "CheckersBoard.hpp"
#include "Constants.hpp"

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
        bool m_canBeCaptured = false;

        std::vector<std::pair<int, int>> m_possibleCaptures;

        bool IsWithinBoard(const CheckersBoard& board, int x, int y) const;
        bool IsOpponentPiece(const CheckersBoard& board, int x, int y) const;
        bool EmptyCell(const CheckersBoard& board, int x, int y) const;
        
        void SimpleMoves(const CheckersBoard& board);
        void CaptureMoves(const CheckersBoard& board);
    public:
        CheckersPiece() = default;
        CheckersPiece(int x, int y, std::shared_ptr<Player> owner, char symbol);
        ~CheckersPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece);

        void FindPossibleMoves(const Board& board) override;

        void SetCanBeCaptured();
        void ResetCanBeCaptured();

        void Promote();
        bool IsPromoted() const;
        bool CanBeCaptured() const;

        std::vector<std::pair<int, int>> GetPossibleCaptures() const;
};
