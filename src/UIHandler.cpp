#include "../include/UIHandler.hpp"

void UIHandler::InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const sf::Font& font, const int &characterSize, const sf::Color& color) const
{
    object.setFont(font);
    object.setString(text);
    object.setCharacterSize(characterSize);
    object.setFillColor(color);
    object.setOrigin(
        object.getGlobalBounds().width / 2,
        object.getGlobalBounds().height / 2
    );
    object.setPosition(position);
}

void UIHandler::InitRectangleShape(sf::RectangleShape &object, const sf::Vector2f &size, const sf::Vector2f &position, const sf::Color &color) const
{
    object.setSize(size);
    object.setPosition(position);
    object.setFillColor(color);
}

void UIHandler::UpdateButtonState(sf::Text &button, bool isSelected, bool isHovered, bool &wasHovered, bool isVisible) const 
{
    if (!isVisible) 
    {
        button.setFillColor(sf::Color::Transparent);
        button.setOutlineColor(sf::Color::Transparent);
        button.setOutlineThickness(0.f);
    }
    else 
    {
        if (isSelected) 
        {
            button.setFillColor(sf::Color::Red);
            button.setOutlineColor(sf::Color::White);
            button.setOutlineThickness(2.f);
        }
        else 
        {
            button.setFillColor(sf::Color::White);
            button.setOutlineColor(sf::Color::Black);
            button.setOutlineThickness(2.f);
        }
        
        if (isHovered && !wasHovered) 
        {
            button.setFillColor(sf::Color::Red);
            button.setOutlineColor(sf::Color::White);
            button.setOutlineThickness(2.f);
            wasHovered = true;
        }
        else if (!isHovered && wasHovered) 
        {
            button.setFillColor(sf::Color::White);
            button.setOutlineColor(sf::Color::Black);
            button.setOutlineThickness(2.f);
            wasHovered = false;
        }
    }
}