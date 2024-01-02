#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Types.hpp"

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
    const std::string BUTIN_TITLE = "Butin - Diamant/Hamdi";
    const std::string CHECKERS_TITLE = "Les Dames - Diamant/Hamdi";
    const std::string BULLTRICKER_TITLE = "Bulltricker - Diamant/Hamdi";
};

namespace AssetsConstants
{
    const std::string MAIN_FONT = "assets/fonts/DejaVuSansMono.ttf";

    const std::string MENUBACKGROUND = "assets/images/menu/background.png";
    
    const std::string CHECKERS_BLACK_PAWN = "assets/images/checkers/black_pawn.png";
    const std::string CHECKERS_WHITE_PAWN = "assets/images/checkers/white_pawn.png";
    const std::string CHECKERS_BLACK_QUEEN = "assets/images/checkers/black_queen.png";
    const std::string CHECKERS_WHITE_QUEEN = "assets/images/checkers/white_queen.png";
    
    const std::string BUTIN_YELLOW_PIECE = "assets/images/butin/yellow_piece.png";
    const std::string BUTIN_RED_PIECE = "assets/images/butin/red_piece.png";
    const std::string BUTIN_BLACK_PIECE = "assets/images/butin/black_piece.png";

    const std::string EMPTY_ASSET = "assets/images/empty.png";
};

namespace UIConstants {
    namespace GameContext {
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
        const sf::Vector2f MENUBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 30.f
        );
    };
    namespace GameChoiceContext {
        const sf::Vector2f BUTINBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 - 25.f
        );
        const sf::Vector2f CHECKERSBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2
        );
        const sf::Vector2f BULLTRICKERBUTTON_POSITION = sf::Vector2f(
            static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
            static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 + 25.f
        );
    };
    const sf::Vector2f GAMETITLE_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 - 150.f
    );
    const sf::Vector2f EXITBUTTON_POSITION = sf::Vector2f(
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) / 2, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) / 2 + 250.f
    );
    const int CHARACTER_SIZE = 20;
};

namespace GameConstants
{
    const sf::Color BLACKCELL_COLOR = sf::Color{112, 74, 39};
    const sf::Color WHITECELL_COLOR = sf::Color{209, 183, 151};

    // Assuming the whole board is clickable
    const auto CLICKABLE_ZONE = std::make_pair(0, 480); 

    const int PLAYER_ONEID = 0;
    const int PLAYER_TWOID = 1;
    const int NONEID = 2;

    const int BOARD_UPPER_LIMIT = 0;
    const int BOARD_LOWER_LIMIT = 9;

    const sf::Color BOARDBACKGROUND_COLOR = sf::Color{46, 24, 3};
    const sf::Vector2f BOARDBACKGROUND_SIZE = sf::Vector2f{
        static_cast<float>(WindowConstants::WINDOW_SIZE.x) - 10.f, 
        static_cast<float>(WindowConstants::WINDOW_SIZE.y) - 110.f
    };
    const sf::Vector2f BOARDBACKGROUND_POSITION = sf::Vector2f{5.f, 5.f};
    const sf::Vector2f BOARDOFFSET = sf::Vector2f{10.f, 10.f};


    inline sf::Vector2f calculateBoardCellSize(const sf::Vector2f& boardBackgroundSize, float rows, float cols, float padding) {
    // Implementation of the function
        return sf::Vector2f{
            (boardBackgroundSize.x - padding) / cols,
            (boardBackgroundSize.y - padding) / rows
        };
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

        const char NOWINNER = -1;

        const char BLACK = 'B';
        const char WHITE = 'W';

        const std::vector<direction_t> WHITE_DIRECTION = {{-1, -1}, {-1, 1}};
        const std::vector<direction_t> BLACK_DIRECTION = {{1, -1}, {1, 1}};
        const std::vector<direction_t> ALL_DIRECTION = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        const sf::Vector2f BOARDCELL_SIZE = sf::Vector2f{
            (BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(CHECKERSROWS),
            (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(CHECKERSCOLS)
        };
        const sf::Vector2f BOARDPIECE_SIZE = sf::Vector2f{
            BOARDCELL_SIZE.x - 10.f, 
            BOARDCELL_SIZE.y - 10.f
        };
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

        const std::vector<direction_t> ALL_DIRECTION = {{1, 0}, {-1, 0}, {0, 1}, {0, -1},    // Linear
                                                        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; // Diagonal
    
     // ajouter les differents boaard celll pour bulltricker
        const sf::Vector2f BOARDCELL_SIZE = sf::Vector2f{
            (BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(BUTINROWS),
            (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(BUTINCOLS)
        };
        const sf::Vector2f BOARDPIECE_SIZE = sf::Vector2f{
            BOARDCELL_SIZE.x - 10.f, 
            BOARDCELL_SIZE.y - 10.f
        };
    };


    namespace BulltrickerConstants{
        const int BULLTRICKERROWS = 15; // Assuming an 8x8 board for Butin
        const int BULLTRICKERCOLS = 15;
        
        const int BLACK_PAWN_ID = 0; // Define IDs for Butin pieces
        const int WHITE_PAWN_ID = 1;
        const int BLACK_QUEEN_ID = 2;
        const int WHITE_QUEEN_ID = 3;
        const int BLACK_KING_ID = 4;
        const int WHITE_KING_ID = 5;
        const int EMPTY_ID = 6;


        const char BLACK = 'B';
        const char WHITE = 'W';


        const std::vector<direction_t> WHITE_DIRECTION = {{-1, -1}, {-1, 1}};
        const std::vector<direction_t> BLACK_DIRECTION = {{1, -1}, {1, 1}};
        const std::vector<direction_t> ALL_DIRECTION = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    
     // ajouter les differents boaard celll pour bulltricker
     
        const sf::Vector2f BUTEE_CELL_SIZE(16.25f, 16.25f);
        const sf::Vector2f HORIZONTAL_RECT_CELL_SIZE(50.0f, 16.25f);
        const sf::Vector2f VERTICAL_RECT_CELL_SIZE(16.25f, 50.0f);
        const sf::Vector2f ROYAL_CELL_SIZE(50.0f, 50.0f);


        // Calculating the sizes for the pieces with padding
        const sf::Vector2f ROYAL_BOARDPIECE_SIZE = sf::Vector2f{
            ROYAL_CELL_SIZE.x - 10.f,  
            ROYAL_CELL_SIZE.y - 10.f
        };
        const sf::Vector2f HORIZONTAL_RECT_BOARDPIECE_SIZE = sf::Vector2f{
            HORIZONTAL_RECT_CELL_SIZE.x - 10.f,
            HORIZONTAL_RECT_CELL_SIZE.y - 10.f
        };
        const sf::Vector2f VERTICAL_RECT_BOARDPIECE_SIZE = sf::Vector2f{
            VERTICAL_RECT_CELL_SIZE.x - 10.f,
            VERTICAL_RECT_CELL_SIZE.y - 10.f
        };
        const sf::Vector2f BUTEE_BOARDPIECE_SIZE = sf::Vector2f{
            BUTEE_CELL_SIZE.x - 10.f,  
            BUTEE_CELL_SIZE.y - 10.f
        };
    };

    };