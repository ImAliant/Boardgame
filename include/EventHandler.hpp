#pragma once

#include <SFML/Graphics.hpp>

class EventHandler
{
    public:
        virtual ~EventHandler() = default;

        virtual void InputUp();
        virtual void InputDown();
        virtual void InputReturn();
        virtual void InputEscape();
};