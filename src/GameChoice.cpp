#include "../include/GameChoice.hpp"
//#include "../include/game/Checkers.hpp"
#include "../include/game/checkers/CheckersController.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

GameChoice::GameChoice(const std::shared_ptr<Context> &context): m_context(context) {}

GameChoice::~GameChoice() {}

void GameChoice::Init() 
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

    // Game 1 button
    InitText(m_butinButton, "Butin", sf::Vector2f(width / 2, height / 2 - 25.f), *font, 20);

    // Checkers game button
    InitText(m_checkersButton, "Les Dames", sf::Vector2f(width / 2, height / 2), *font, 20);

    // Game 3 button
    InitText(m_bulltrickerButton, "Bulltricker", sf::Vector2f(width / 2, height / 2 + 25.f), *font, 20);

    // Exit button
    InitText(m_exitButton, "Quitter", sf::Vector2f(width / 2, height / 2 + 250.f), *font, 20);
}

void GameChoice::Update()
{
    if(m_isButinButtonSelected) ActionButinButtonSelected();
    else if(m_isCheckersButtonSelected) ActionCheckersButtonSelected();
    else if(m_isBulltrickerButtonSelected) ActionBulltrickerButtonSelected();
    else if(m_isExitButtonSelected) ActionExitButtonSelected();

    if(m_isButinButtonPressed)
    {
        // TODO : Change the current state to Game1
        std::cout << "Butin" << std::endl;

        m_isButinButtonPressed = false;
    }
    else if(m_isCheckersButtonPressed)
    {
        //m_context->m_states->Add(std::make_unique<Checkers>(m_context), true);
        // TODO
        m_context->m_states->Add(std::make_unique<CheckersController>(m_context), true);

        m_isCheckersButtonPressed = false;
    }
    else if(m_isBulltrickerButtonPressed)
    {
        std::cout << "Bulltricker" << std::endl;
        // TODO : Change the current state to Game3

        m_isBulltrickerButtonPressed = false;
    }
    else if(m_isExitButtonPressed)
    {
        m_context->m_states->PopAll();
        m_context->m_window->close();
    }
}

void GameChoice::ActionButinButtonSelected()
{
    // TODO controller si le bouton est bien selectionné
    m_butinButton.setFillColor(sf::Color::Red);
    m_checkersButton.setFillColor(sf::Color::White);
}
void GameChoice::ActionCheckersButtonSelected()
{
    // TODO controller si le bouton est bien selectionné
    m_checkersButton.setFillColor(sf::Color::Red);
    m_butinButton.setFillColor(sf::Color::White);
    m_bulltrickerButton.setFillColor(sf::Color::White);
}
void GameChoice::ActionBulltrickerButtonSelected()
{
    // TODO controller si le bouton est bien selectionné
    m_bulltrickerButton.setFillColor(sf::Color::Red);
    m_checkersButton.setFillColor(sf::Color::White);
    m_exitButton.setFillColor(sf::Color::White);
}
void GameChoice::ActionExitButtonSelected()
{
    // TODO controller si le bouton est bien selectionné
    m_exitButton.setFillColor(sf::Color::Red);
    m_bulltrickerButton.setFillColor(sf::Color::White);
}

void GameChoice::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) 
    {
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

void GameChoice::InputUp() 
{
    if (m_isCheckersButtonSelected)
    {
        m_isCheckersButtonSelected = false;
        m_isButinButtonSelected = true;
    }
    else if (m_isBulltrickerButtonSelected)
    {
        m_isBulltrickerButtonSelected = false;
        m_isCheckersButtonSelected = true;
    }
    else if (m_isExitButtonSelected)
    {
        m_isExitButtonSelected = false;
        m_isBulltrickerButtonSelected = true;
    }
}

void GameChoice::InputDown() 
{
    if (m_isButinButtonSelected)
    {
        m_isButinButtonSelected = false;
        m_isCheckersButtonSelected = true;
    }
    else if (m_isCheckersButtonSelected)
    {
        m_isCheckersButtonSelected = false;
        m_isBulltrickerButtonSelected = true;
    }
    else if (m_isBulltrickerButtonSelected)
    {
        m_isBulltrickerButtonSelected = false;
        m_isExitButtonSelected = true;
    }
}

void GameChoice::InputReturn()
{
    resetButtonValues();

    if (m_isButinButtonSelected) m_isButinButtonPressed = true;
    else if (m_isCheckersButtonSelected) m_isCheckersButtonPressed = true;
    else if (m_isBulltrickerButtonSelected) m_isBulltrickerButtonPressed = true;
    else if (m_isExitButtonSelected) m_isExitButtonPressed = true;
}

void GameChoice::resetButtonValues()
{
    m_isButinButtonPressed = false;
    m_isCheckersButtonPressed = false;
    m_isBulltrickerButtonPressed = false;
    m_isExitButtonPressed = false;
}

void GameChoice::InputEscape()
{
    m_context->m_states->PopAll();
    m_context->m_window->close();
}

void GameChoice::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_butinButton);
    m_context->m_window->draw(m_checkersButton);
    m_context->m_window->draw(m_bulltrickerButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

/*void GameChoice::InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize)
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