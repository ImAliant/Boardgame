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
    const sf::Vector2f PLAYERTEXT_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 8, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 50.f
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
    const int BLACKPAWN_ID = 0;
    const int WHITEPAWN_ID = 1;
    const int BLACKQUEEN_ID = 2;
    const int WHITEQUEEN_ID = 3;
    const int EMPTY_ID = 4;

    const char BLACK = 'B';
    const char WHITE = 'W';
    const char TRANSPARENT = 'T';

    const auto CLICKABLE_ZONE = std::make_pair(10, 480);
    const int PLAYER_ONEID = 0;
    const int PLAYER_TWOID = 1;
    const int NONEID = 2;

    const int BOARD_UPPER_LIMIT = 0;
    const int BOARD_LOWER_LIMIT = 9;

    const std::vector<std::pair<int, int>> WHITE_DIRECTION = {{-1, -1}, {-1, 1}};
    const std::vector<std::pair<int, int>> BLACK_DIRECTION = {{1, -1}, {1, 1}};
    const std::vector<std::pair<int, int>> ALL_DIRECTION = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

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


namespace ButinConstants
{
    const int BUTINROWS = 8; // Assuming an 8x8 board for Butin
    const int BUTINCOLS = 8;
    
    const int YELLOW_PAWN_ID = 0; // Define IDs for Butin pieces
    const int RED_PAWN_ID = 1;
    const int BLACK_PAWN_ID = 2;
    const int EMPTY_ID = 3;

    const char BUTIN_YELLOW = 'Y'; // Define character symbols for Butin pieces
    const char BUTIN_RED = 'R';
    const char BUTIN_BLACK = 'B';
    const char TRANSPARENT = 'T';

    // Assuming the whole board is clickable
    const auto CLICKABLE_ZONE = std::make_pair(0, 480); 

    
    const int PLAYER_ONEID = 0;
    const int PLAYER_TWOID = 1;
    const int NONEID = 2;

    const int BOARD_UPPER_LIMIT = 0;
    const int BOARD_LOWER_LIMIT = 9;

    const sf::Color BLACKCELL_COLOR = sf::Color{112, 74, 39};
    const sf::Color WHITECELL_COLOR = sf::Color{209, 183, 151};
    const sf::Color BOARDBACKGROUND_COLOR = sf::Color{46, 24, 3};
    const sf::Vector2f BOARDBACKGROUND_SIZE = sf::Vector2f{
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) - 10.f, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 110.f
    };
    const sf::Vector2f BOARDBACKGROUND_POSITION = sf::Vector2f{5.f, 5.f};
    const sf::Vector2f BOARDCELL_SIZE = sf::Vector2f{
        (BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(BUTINROWS),
        (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(BUTINCOLS)
    };
    const sf::Vector2f BOARDPIECE_SIZE = sf::Vector2f{
        BOARDCELL_SIZE.x - 10.f, 
        BOARDCELL_SIZE.y - 10.f
    };
    const sf::Vector2f BOARDOFFSET = sf::Vector2f{10.f, 10.f};
};

