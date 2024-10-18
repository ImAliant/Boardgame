#pragma once

#include <iostream>
#include <memory>

#include "Types.hpp"
#include "game/Piece.hpp"

class Piece;

class Move
{
    private:
        const coord_t from;
        const coord_t to;
        const std::shared_ptr<Piece> piece;

        bool is_jump;
    public:
        Move(const coord_t f, const coord_t t, const std::shared_ptr<Piece> p = nullptr);
        ~Move() = default;

        bool IsJump() const;

        coord_t GetFrom() const;
        coord_t GetTo() const;
        std::shared_ptr<Piece> GetPiece() const;

        friend std::ostream& operator<<(std::ostream& os, const Move& m);
};