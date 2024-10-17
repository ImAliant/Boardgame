#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Board.hpp"
#include "Types.hpp"

class Board;

class Piece
{
    private:
        coord_t coord;
        const char symbol;
        std::vector<coord_t> possible_moves;
    protected:
        virtual void FindSimpleMoves(std::shared_ptr<Board> board) = 0;
        virtual void FindJumpMoves(std::shared_ptr<Board> board) = 0;
    public:
        explicit Piece(const coord_t c, const char s = 'O');
        virtual ~Piece() = default;

        virtual void SetPossibleMoves(std::shared_ptr<Board> board) = 0;
        void AddPossibleMove(const coord_t c);
        void ClearPossibleMoves();

        void SetCoord(const coord_t c);

        coord_t GetCoord() const;
        char GetSymbol() const;
};