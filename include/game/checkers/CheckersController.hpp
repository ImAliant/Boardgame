#pragma once

#include "Checkers.hpp"
#include "CheckersView.hpp"
#include "../Controller.hpp"

#include <memory>
#include <vector>

class CheckersController: public Controller
{
    private:
        void End() override;

        void PrintAndResetPlayer() const override;

        void SetWindowTitle() const override;
    public:
        explicit CheckersController(std::shared_ptr<Context> context);
        ~CheckersController() override = default;
};