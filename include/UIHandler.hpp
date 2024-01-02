#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Launcher.hpp"

class UIHandler
{
protected:
    virtual ~UIHandler() = default;
    void InitText(sf::Text &object, const std::string &text, 
                  const sf::Vector2f &position, const sf::Font& font, 
                  const int &characterSize = 30);
    void InitRectangleShape(sf::RectangleShape &object, const sf::Vector2f &size, const sf::Vector2f &position) const;
    void UpdateButtonState(sf::Text &button, bool isSelected, bool isHovered, bool &wasHovered, bool isVisible = true) const;
};