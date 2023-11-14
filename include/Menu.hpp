#ifndef _MENU
#define _MENU

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameType.hpp"

const std::string TITLE = "BoardGame - Menu";
const std::string FONT_PATH = "../assets/fonts/DejaVuSansMono.ttf";
const unsigned int _TITLE_TEXT_SIZE = 30;
const unsigned int _GAME_TEXT_SIZE = 20;

const unsigned int _WINDOW_WIDTH = 350;
const unsigned int _WINDOW_HEIGHT = 150;

struct TextGame {
    sf::Text text;
    GameType gameType;
};

class Menu {
    public:
        explicit Menu();
        virtual ~Menu();
        
        void run();
    private:
        sf::RenderWindow window;
        sf::Font font;
        sf::Text titreFenetre;
        std::vector<TextGame> jeux;

        void handleClickOnText(const TextGame& game, const sf::Event& event) const;
        void initializeText(sf::Text &text, const sf::Color &color, const unsigned int &size, const float &x, const float &y) const;
        void windowLoop();
        void display();
        void launchGame(GameType gameType) const;
        static Game* createGame(GameType gameType);
        void loadFont();
        void loadTexts();
        void loadWindow();
        void loadGames();
        void load();
};

#endif