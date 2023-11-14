#include "../include/CheckersPiece.hpp"

#include <iostream>

CheckersPiece::~CheckersPiece()
{
    std::cout << "CheckersPiece::~CheckersPiece()" << std::endl;
}

char CheckersPiece::getSymbol() const
{
    return (getPlayer().getPlayer() == Players::P1) ? 'x' : 'o';
}

bool CheckersPiece::IsKing() const
{
    return isKing;
}