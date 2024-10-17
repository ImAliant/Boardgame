#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "game/Piece.hpp"

class Player
{
    private:
        static int idCounter;

        int id;
        int score;

        std::vector<std::shared_ptr<Piece>> pieces;
    public:
        explicit Player();
        virtual ~Player() = default;

        void AddPiece(std::shared_ptr<Piece> piece);

        int GetId() const;
        int GetScore() const;
        std::vector<std::shared_ptr<Piece>> GetPieces() const;

        friend std::ostream& operator<<(std::ostream& os, const Player& player);
};