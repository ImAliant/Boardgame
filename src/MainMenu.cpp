#include "../include/MainMenu.hpp"
#include "../include/GameChoice.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(const std::shared_ptr<Context> &context): m_context(context) {}
MainMenu::~MainMenu() {}

void MainMenu::Init()
{
    auto width = static_cast<float>(m_context->m_window->getSize().x);
    auto height = static_cast<float>(m_context->m_window->getSize().y);

    sf::Font const* font = &m_context->m_assets->GetFont(MAIN_FONT);
    if (font == nullptr)
    {
        std::cout << "The font of is not loaded" << std::endl;
        return;
    }

    // Title
    InitText(m_gameTitle, "Boardgame", sf::Vector2f(width / 2, height / 2 - 150.f), *font);

    // Play button
    InitText(m_choiceButton, "Jeux", sf::Vector2f(width / 2, height / 2), *font, 20);

    // Exit button
    InitText(m_exitButton, "Quitter", sf::Vector2f(width / 2, height / 2 + 250.f), *font, 20);
}

void MainMenu::Update()
{
    if (m_isChoiceButtonSelected)
    {
        m_choiceButton.setFillColor(sf::Color::Red);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Red);
        m_choiceButton.setFillColor(sf::Color::White);
    }

    if (m_isChoiceButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GameChoice>(m_context), true);

        m_isChoiceButtonPressed = false;
    }
    else if (m_isExitButtonPressed) {
        m_context->m_states->PopAll();
        m_context->m_window->close();
    }
}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                    InputUp();
                    break;
                case sf::Keyboard::Down:
                    InputDown();
                    break;
                case sf::Keyboard::Return:
                    InputReturn();
                    break;
                case sf::Keyboard::Escape:
                    InputEscape();
                    break;
                default:
                    break;
            }
        }
    }
}

void MainMenu::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_choiceButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

void MainMenu::InputUp()
{
    if (!m_isChoiceButtonSelected)
    {
        m_isChoiceButtonSelected = true;
        m_isExitButtonSelected = false;
    }
}

void MainMenu::InputDown()
{
    if (!m_isExitButtonSelected)
    {
        m_isExitButtonSelected = true;
        m_isChoiceButtonSelected = false;
    }
}

void MainMenu::InputReturn()
{
    m_isChoiceButtonPressed = false;
    m_isExitButtonPressed = false;

    if (m_isChoiceButtonSelected) m_isChoiceButtonPressed = true;
    else m_isExitButtonPressed = true;
}

void MainMenu::InputEscape()
{
    m_context->m_states->PopAll();
    m_context->m_window->close();
}

/*void MainMenu::InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize)
{
    sf::Font const* font = &m_context->m_assets->GetFont(MAIN_FONT); 
    if (font == nullptr)
    {
        std::cout << "The font of is not loaded" << std::endl;
        return;
    }

    object.setFont(*font);
    object.setString(text);
    object.setCharacterSize(characterSize);
    object.setOrigin(object.getGlobalBounds().width / 2, object.getGlobalBounds().height / 2);
    object.setPosition(position);
}*/