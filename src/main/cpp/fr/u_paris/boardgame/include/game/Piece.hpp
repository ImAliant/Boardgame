#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Board.hpp"
#include "Types.hpp"
#include "movement/Move.hpp"

class Board;
class Move;

class Piece
{
    private:
        coord_t coord;
        const char symbol;
        std::vector<std::shared_ptr<Move>> possible_moves;
    protected:
        virtual void FindMoves(std::shared_ptr<Board> board) = 0;
        virtual void HandlePieceEncounter(const coord_t& to, const dir_t& dir, std::shared_ptr<Board> board) = 0;
    public:
        explicit Piece(const coord_t c, const char s = 'O');
        virtual ~Piece() = default;

        void SetPossibleMoves(std::shared_ptr<Board> board);
        void AddPossibleMove(const std::shared_ptr<Move> m);
        void ClearPossibleMoves();

        void SetCoord(const coord_t c);

        coord_t GetCoord() const;
        char GetSymbol() const;
        std::vector<std::shared_ptr<Move>> GetPossibleMoves() const;

        friend std::ostream& operator<<(std::ostream& os, const Piece& p);
};