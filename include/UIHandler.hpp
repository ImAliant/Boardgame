#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Launcher.hpp"

namespace UI
{
    class UIHandler
    {
    public:
        virtual ~UIHandler() = default;

        virtual void InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const sf::Font& font, const int &characterSize = 30) {
            object.setFont(font);
            object.setString(text);
            object.setCharacterSize(characterSize);
            object.setOrigin(
                object.getGlobalBounds().width / 2,
                object.getGlobalBounds().height / 2
            );
            object.setPosition(position);
        };
        virtual void InitSizeAndPositionRectangleShape(sf::RectangleShape &object, const sf::Vector2f &size, const sf::Vector2f &position) {
            object.setSize(size);
            object.setPosition(position);
        };
        virtual void UpdateButtonState(sf::Text &button, bool isSelected, bool isHovered, bool &wasHovered, bool isVisible = true) {
            if (!isVisible) {
                button.setFillColor(sf::Color::Transparent);
                button.setOutlineColor(sf::Color::Transparent);
                button.setOutlineThickness(0.f);
            }
            else {
                if (isSelected) {
                    button.setFillColor(sf::Color::Red);
                    button.setOutlineColor(sf::Color::White);
                    button.setOutlineThickness(2.f);
                }
                else {
                    button.setFillColor(sf::Color::White);
                    button.setOutlineColor(sf::Color::Red);
                    button.setOutlineThickness(2.f);
                }

                if (isHovered && !wasHovered) {
                    button.setFillColor(sf::Color::Red);
                    button.setOutlineColor(sf::Color::White);
                    button.setOutlineThickness(2.f);
                    wasHovered = true;
                }
                else if (!isHovered && wasHovered) {
                    button.setFillColor(sf::Color::White);
                    button.setOutlineColor(sf::Color::Red);
                    button.setOutlineThickness(2.f);
                    wasHovered = false;
                }
            }
        };
    };
};