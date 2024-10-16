#pragma once

#include <memory>

#include "Board.hpp"

class Game
{
    protected: 
        std::shared_ptr<Board> board;
        virtual void Init() = 0;
    public:
        explicit Game();
        virtual ~Game() = default;

        std::shared_ptr<Board> GetBoard() const;
};