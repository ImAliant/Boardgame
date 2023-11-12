#include "../include/Menu.hpp"
#include "../include/FontNotFoundException.hpp"
#include "../include/CheckersGame.hpp"

#include <iostream>

using namespace std;

Menu::Menu() 
{
    load();
}

Menu::~Menu()
{
    cout << "Menu::~Menu" << endl;
}

void Menu::run() 
{
    windowLoop();
}

void Menu::windowLoop() 
{
    while (window.isOpen()) 
    {
        sf::Event event{};
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (auto const &game : jeux)
                handleClickOnText(game.first, event, game.second);
        }

        display();
    }
}

void Menu::handleClickOnText(const sf::Text& game, const sf::Event& event, GameType gameType) const
{
    bool isButtonPressed = event.type == sf::Event::MouseButtonPressed;
    bool isMouseLeft = event.mouseButton.button == sf::Mouse::Left;
    bool isMouseLeftButtonPressed = isButtonPressed && isMouseLeft;
    
    if (isMouseLeftButtonPressed)
    {
        sf::FloatRect textBounds = game.getGlobalBounds();
        auto x = static_cast<float>(event.mouseButton.x);
        auto y = static_cast<float>(event.mouseButton.y);
        auto mousePos = sf::Vector2f(x, y);

        if (textBounds.contains(mousePos))
        {
            switch (gameType) 
            {
                case GameType::Checkers:
                    cout << "Checkers" << endl;
                    launchGame(gameType);
                    break;
                case GameType::Jeu2:
                    cout << "Jeu 2" << endl;
                    launchGame(gameType);
                    break;
                case GameType::Jeu3:
                    cout << "Jeu 3" << endl;
                    launchGame(gameType);
                    break;
            }
        }
    }
}

void Menu::load() 
{
    loadGames();
    loadFont();
    loadTexts();
    loadWindow();
}

void Menu::loadFont() 
{
    try 
    {
        if (!font.loadFromFile(FONT_PATH))
            throw FontNotFoundException("Font not found !");
    } catch (const FontNotFoundException& e) 
    {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void Menu::initializeText(sf::Text &text, const sf::Color &color, const unsigned int &size, const float &x, const float &y) const 
{
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
}

void Menu::loadTexts() 
{
    titreFenetre.setString("BoardGame");
    initializeText(titreFenetre, sf::Color::White, _TITLE_TEXT_SIZE, (static_cast<float>(window.getSize().x) - titreFenetre.getGlobalBounds().width) / 2, 10);
    
    jeux[0].first.setString("Jeu 1");
    initializeText(jeux[0].first, sf::Color::White, _GAME_TEXT_SIZE, (static_cast<float>(window.getSize().x) - jeux[0].first.getGlobalBounds().width) / 2, 50);
    
    jeux[1].first.setString("Jeu 2");
    initializeText(jeux[1].first, sf::Color::White, _GAME_TEXT_SIZE, (static_cast<float>(window.getSize().x) - jeux[1].first.getGlobalBounds().width) / 2, 80);
    
    jeux[2].first.setString("Jeu 3");
    initializeText(jeux[2].first, sf::Color::White, _GAME_TEXT_SIZE, (static_cast<float>(window.getSize().x) - jeux[2].first.getGlobalBounds().width) / 2, 110);
}

void Menu::loadWindow() 
{
    window.create(sf::VideoMode(_WINDOW_WIDTH, _WINDOW_HEIGHT), "BoardGame - DiamantHamdi");

    const auto desktopMode = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktopMode.width / 2 - window.getSize().x / 2,
                                    desktopMode.height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(60);
}

void Menu::display() 
{
    window.clear();
    window.draw(titreFenetre);
    for (auto const& jeu : jeux)
        window.draw(jeu.first);
    window.display();
}

void Menu::loadGames() 
{
    jeux.emplace_back(sf::Text(), GameType::Checkers);
    jeux.emplace_back(sf::Text(), GameType::Jeu2);
    jeux.emplace_back(sf::Text(), GameType::Jeu3);
}

void Menu::launchGame(GameType gameType) const
{
    switch (gameType) 
    {
        case GameType::Checkers:
            launchCheckersGame();
            break;
        case GameType::Jeu2:
            break;
        case GameType::Jeu3:
            break;
    }
}

void Menu::launchCheckersGame() const
{
    CheckersGame game;
    game.run();
}

void Menu::unload() 
{
    window.close();
}