#pragma once

#include "Piece.hpp"
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
    public:
        CheckersPiece() = default;
        CheckersPiece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol);
        ~CheckersPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const CheckersPiece& piece);

        void FindPossibleMoves(const Board& board) override;

        void Promote();
        bool IsPromoted() const;
};
