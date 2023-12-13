#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics/Color.hpp>

#include "Player.hpp"
#include "Board.hpp"

class Board;

struct state_t {
        int type;
        sf::Color m_color;
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

        std::vector<std::pair<int, int>> m_possibleMoves;
    public:
        Piece();
        Piece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol);
        virtual ~Piece() = default;

        virtual void FindPossibleMoves(const Board& board) = 0;

        void SetPosition(int x, int y);

        std::vector<std::pair<int, int>> GetPossibleMoves() const;
        std::pair<int, int> GetPosition() const;
        Player& GetOwner() const;
        sf::Color GetColor() const;
        char GetSymbol() const;
};