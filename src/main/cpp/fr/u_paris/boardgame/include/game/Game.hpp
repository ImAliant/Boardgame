#pragma once

#include <memory>

#include "Board.hpp"

class Game
{
    private:
        std::shared_ptr<Board> board;

    protected: 
        void Init();
    public:
        explicit Game();
        virtual ~Game() = default;

        /* virtual void Start() = 0;
        virtual void Play() = 0;
        virtual void End() = 0; */

        std::shared_ptr<Board> GetBoard() const;
};