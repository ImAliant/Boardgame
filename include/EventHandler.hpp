#pragma once

#include <SFML/Graphics.hpp>

class EventHandler
{
    public:
        virtual ~EventHandler() = default;

        virtual void UpdateButtonHoverState(const sf::Event& event);
        virtual void UpdateButtonSelectionState();
        virtual void HandleMousePressed(const sf::Event& event);

        virtual void InputUp();
        virtual void InputDown();
        virtual void InputReturn();
        virtual void InputEscape();
};