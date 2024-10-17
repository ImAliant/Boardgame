#pragma once

#include <memory>

#include "Game.hpp"
#include "View.hpp"

class Controller
{
    protected:
        std::shared_ptr<Game> game;
        std::shared_ptr<View> view;
    public:
        explicit Controller(std::shared_ptr<Game> game, std::shared_ptr<View> view);
        virtual ~Controller() = default;

        virtual void Start();
};