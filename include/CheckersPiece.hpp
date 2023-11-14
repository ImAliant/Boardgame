#ifndef _CHECKERSPIECE
#define _CHECKERSPIECE

#include "Piece.hpp"

class CheckersPiece: Piece
{
    public:
        using Piece::Piece;
        ~CheckersPiece() override;

        char getSymbol() const;
        bool IsKing() const;
    private:
        bool isKing = false;
};

#endif