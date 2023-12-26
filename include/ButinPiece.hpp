#pragma once

#include "Piece.hpp"
#include "ButinBoard.hpp"
#include "Constants.hpp"

class ButinBoard;

enum Butin_PieceType
{
    BUTIN_EMPTY,
    YELLOW,
    RED,
    BLACK
};

class ButinPiece: public Piece
{
    private:
        bool m_canBeCaptured = false;

        std::vector<std::pair<int, int>> m_possibleCaptures;

        bool IsWithinBoard(const ButinBoard& board, int x, int y) const;
       
        bool EmptyCell(const ButinBoard& board, int x, int y) const;
        
       
    public:
        ButinPiece() = default;
        ButinPiece(int x, int y,  char symbol);
        ~ButinPiece() override;

        friend std::ostream& operator<<(std::ostream& os, const ButinPiece& piece);

        void FindPossibleMoves(const Board& board) override;

       
        bool HasPieceToJump(const ButinBoard& board,int currentX, int currentY, int nextX, int nextY);
        
        

        std::vector<std::pair<int, int>> GetPossibleCaptures() const;

     
};
