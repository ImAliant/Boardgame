#ifndef _MENU
#define _MENU

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Menu {
    public:
        Menu();
        void run();
    private:
        sf::RenderWindow window;
        sf::Font font;
        sf::Text titreFenetre;
        std::vector<std::pair<sf::Text, GameType>> jeux;
        void handleClickOnText(const sf::Text& game, const sf::Event& event, GameType gameType);
        void textDesignAndPosition(sf::Text &text, const sf::Color &color, const float &x, const float &y);
        void windowLoop();
        void launchCheckersGame();
        void launchGame(GameType gameType);
        void loadFont();
        void loadTexts();
        void loadWindow();
        void loadGames();
        void load();
        void unload();
};

#endif