#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics/Color.hpp>

#include "Player.hpp"
#include "Board.hpp"

class Board;

class Piece 
{
    private:
        int m_x;
        int m_y;
        sf::Color m_color;
        std::shared_ptr<Player> m_owner;

        std::vector<std::pair<int, int>> m_possibleMoves;

        char m_symbol;
    public:
        Piece();
        Piece(int x, int y, std::shared_ptr<Player> owner, sf::Color color, char symbol);
        ~Piece();

        Piece& operator=(const Piece& piece);
        friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

        void findPossibleMoves(const Board& board,GameType gameType);

        void setPosition(int x, int y);

        std::vector<std::pair<int, int>> getPossibleMoves() const;

        std::pair<int, int> getPosition() const;
        Player& getOwner() const;
        sf::Color getColor() const;
        char getSymbol() const;
};