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

        /*sf::Color m_color;
        std::shared_ptr<Player> m_owner;
        char m_symbol;*/
    public:
        Piece();
        Piece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol);
        virtual ~Piece() = default;

        /*Piece& operator=(const Piece& piece);
        friend std::ostream& operator<<(std::ostream& os, const Piece& piece);*/

        //void findPossibleMoves(const Board& board);
        virtual void findPossibleMoves(const Board& board) = 0;

        void setPosition(int x, int y);

        std::vector<std::pair<int, int>> getPossibleMoves() const;
        std::pair<int, int> getPosition() const;
        Player& getOwner() const;
        sf::Color getColor() const;
        char getSymbol() const;
};