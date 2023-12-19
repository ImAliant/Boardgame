#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics/Color.hpp>

#include "Player.hpp"
#include "Board.hpp"

class Board;

struct state_t {
    int type = 0;
    std::shared_ptr<Player> m_owner;
    char m_symbol;
};

/*
 * Piece interface
 */
class Piece 
{
    protected:
        int m_x;
        int m_y;

        state_t m_state;

        std::vector<coord_t> m_possibleMoves;
    public:
        Piece();
        Piece(coord_t coord, std::shared_ptr<Player> owner, char symbol);
        virtual ~Piece() = default;

        virtual void FindPossibleMoves(const Board& board) = 0;

        void SetPosition(coord_t coord);

        std::vector<coord_t> GetPossibleMoves() const;
        coord_t GetPosition() const;
        int GetX() const;
        int GetY() const;
        std::shared_ptr<Player> GetOwner() const;
        char GetSymbol() const;
};