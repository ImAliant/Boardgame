#pragma once

#include "Piece.hpp"

class Board; // TODO: CheckersBoard

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

        void findPossibleMoves(const Board& board) override;

        void promote();
        bool isPromoted() const;
};
