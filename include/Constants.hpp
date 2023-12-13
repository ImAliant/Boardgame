#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace WindowConstants
{
    const auto WINDOW_SIZE = sf::Vector2i{500, 600};
    const auto FRAMERATE_LIMIT = 60;
    const auto VERTICAL_SYNC_ENABLED = true;
    const auto WINDOW_POSITION = sf::Vector2i{
        static_cast<int>(sf::VideoMode::getDesktopMode().width / 2 - WINDOW_SIZE.x / 2), 
        static_cast<int>(sf::VideoMode::getDesktopMode().height / 2 - WINDOW_SIZE.y / 2)
    };
    const std::string WINDOW_TITLE = "Boardgame - Diamant/Hamdi";
};

namespace UIConstants {
    const sf::Vector2f LINESEPARATOR_SIZE = sf::Vector2f(static_cast<float>(WindowConstants::WINDOW_SIZE.x), 2.f);
    const sf::Vector2f LINESEPARATOR_POSITION = sf::Vector2f(0.f, static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 100.f);
    const sf::Vector2f LAUNCHBUTTON_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 80.f
    );
    const sf::Vector2f EXITBUTTON_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 30.f
    );
    const int CHARACTER_SIZE = 20;
};

namespace CheckersConstants
{
    const int CHECKERSROWS = 10;
    const int CHECKERSCOLS = 10;
    const int BLACKPIECE_TEXTUREID = 0;
    const int WHITEPIECE_TEXTUREID = 1;
    const auto CLICKABLE_ZONE = std::make_pair(10, 480);

    const sf::Color BLACKCELL_COLOR = sf::Color{112, 74, 39};
    const sf::Color WHITECELL_COLOR = sf::Color{209, 183, 151};
    const sf::Color BOARDBACKGROUND_COLOR = sf::Color{46, 24, 3};
    const sf::Vector2f BOARDBACKGROUND_SIZE = sf::Vector2f{
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) - 10.f, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 110.f
    };
    const sf::Vector2f BOARDBACKGROUND_POSITION = sf::Vector2f{5.f, 5.f};
    const sf::Vector2f BOARDCELL_SIZE = sf::Vector2f{
        (BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(CHECKERSROWS),
        (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(CHECKERSCOLS)
    };
    const sf::Vector2f BOARDPIECE_SIZE = sf::Vector2f{
        BOARDCELL_SIZE.x - 10.f, 
        BOARDCELL_SIZE.y - 10.f
    };
    const sf::Vector2f BOARDOFFSET = sf::Vector2f{10.f, 10.f};
};