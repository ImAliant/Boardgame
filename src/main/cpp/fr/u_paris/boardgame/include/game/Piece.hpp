#pragma once

#include <iostream>

#include "Types.hpp"

class Piece
{
    private:
        coord_t coord;
        const char symbol;
    public:
        explicit Piece(const coord_t c, const char s = 'O');
        virtual ~Piece() = default;

        void SetCoord(const coord_t c);

        coord_t GetCoord() const;
        char GetSymbol() const;
};