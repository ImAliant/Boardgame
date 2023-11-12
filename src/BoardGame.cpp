#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../include/FontNotFoundException.hpp"
#include "../include/Game.hpp"
#include "../include/CheckersGame.hpp"

using namespace std;
using namespace sf;

void launchCheckersGame() {
    CheckersGame checkersGame;
    checkersGame.run();
}

void handleClickOnText(const Text& game, const Event& event, GameType gameType)
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Verifie si le clic est sur le texte
        FloatRect textBounds = game.getGlobalBounds();
        auto mousePos = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        
        if (textBounds.contains(mousePos)) {
            // Affiche le jeu correspondant
            switch (gameType) {
                case GameType::Checkers:
                    cout << "Checkers" << endl;
                    launchCheckersGame();
                    break;
                case GameType::Jeu2:
                    cout << "Jeu 2" << endl;
                    break;
                case GameType::Jeu3:
                    cout << "Jeu 3" << endl;
                    break;
            }
        }
    }
}

void textDesignAndPosition(Text &text, const Color &color, const float &x, const float &y)
{
    text.setFillColor(color);
    text.setPosition(x, y);
}

unique_ptr<RenderWindow> createWindow() {
    auto window = unique_ptr<RenderWindow>(new RenderWindow{VideoMode(350, 200), "BoardGame - DiamantHamdi"});

    const auto desktopMode = VideoMode::getDesktopMode();
    window->setPosition(Vector2i(desktopMode.width / 2 - window->getSize().x / 2,
                                desktopMode.height / 2 - window->getSize().y / 2));
    window->setFramerateLimit(60);
           
    return window;
}

void windowLoop(RenderWindow& window, const Text &titreFenetre, const vector<std::pair<Text, GameType>> &jeux)
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            for (auto const& jeu : jeux)
                handleClickOnText(jeu.first, event, jeu.second);
        }

        window.clear();
        window.draw(titreFenetre);
        for (auto const& jeu : jeux)
            window.draw(jeu.first);
        window.display();
    }
}

int main()
{
    /*auto window = createWindow();

    Font font;
    try {
        if (!font.loadFromFile("../assets/fonts/DejaVuSansMono.ttf"))
            throw FontNotFoundException("Font not found !");
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }

    Text titreFenetre {"Boardgame", font, 30};
    textDesignAndPosition(titreFenetre, Color::White, (static_cast<float>(window->getSize().x) - titreFenetre.getGlobalBounds().width) / 2, 0);

    vector<std::pair<Text, GameType>> jeux {
        {{"Dames", font, 20}, GameType::Checkers},
        {{"Jeu 2", font, 20}, GameType::Jeu2},
        {{"Jeu 3", font, 20}, GameType::Jeu3}
    };

    float offset = 50.0f;
    for (auto& jeu : jeux) {
        textDesignAndPosition(jeu.first, Color::White, (static_cast<float>(window->getSize().x) - jeu.first.getGlobalBounds().width) / 2, offset);
        offset += 50.0f;
    }

    windowLoop(*window, titreFenetre, jeux);*/

    return EXIT_SUCCESS;
}
