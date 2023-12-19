#include "../include/GameChoice.hpp"
#include "../include/game/checkers/CheckersController.hpp"
#include "../include/Constants.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

GameChoice::GameChoice(const std::shared_ptr<Context> &context): m_context(context) {}

GameChoice::~GameChoice() {}

void GameChoice::Init() 
{
    using namespace UIConstants;
    using namespace UIConstants::GameChoiceContext;

    sf::Font const* font = &m_context->m_assets->GetFont(MAIN_FONT);
    if (font == nullptr)
    {
        throw std::runtime_error("MainMenu::Init() : font is nullptr");
    }

    // Title
    InitText(m_gameTitle, "Boardgame", GAMETITLE_POSITION, *font);

    // Game 1 button
    InitText(m_butinButton, "Butin", BUTINBUTTON_POSITION, *font, CHARACTER_SIZE);

    // Checkers game button
    InitText(m_checkersButton, "Les Dames", CHECKERSBUTTON_POSITION, *font, CHARACTER_SIZE);

    // Game 3 button
    InitText(m_bulltrickerButton, "Bulltricker", BULLTRICKERBUTTON_POSITION, *font, CHARACTER_SIZE);

    // Exit button
    InitText(m_exitButton, "Quitter", EXITBUTTON_POSITION, *font, CHARACTER_SIZE);
}

void GameChoice::Update()
{
    if(m_isButinButtonSelected) ActionButinButtonSelected();
    else if(m_isCheckersButtonSelected) ActionCheckersButtonSelected();
    else if(m_isBulltrickerButtonSelected) ActionBulltrickerButtonSelected();
    else if(m_isExitButtonSelected) ActionExitButtonSelected();

    if(m_isButinButtonPressed)
    {
        // TODO : Change the current state to Butin
        std::cout << "Butin" << std::endl;

        m_isButinButtonPressed = false;
    }
    else if(m_isCheckersButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<CheckersController>(m_context), true);

        m_isCheckersButtonPressed = false;
    }
    else if(m_isBulltrickerButtonPressed)
    {
        std::cout << "Bulltricker" << std::endl;
        // TODO : Change the current state to Bulltricker

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
    m_butinButton.setFillColor(sf::Color::Red);
    m_checkersButton.setFillColor(sf::Color::White);
}
void GameChoice::ActionCheckersButtonSelected()
{
    m_checkersButton.setFillColor(sf::Color::Red);
    m_butinButton.setFillColor(sf::Color::White);
    m_bulltrickerButton.setFillColor(sf::Color::White);
}
void GameChoice::ActionBulltrickerButtonSelected()
{
    m_bulltrickerButton.setFillColor(sf::Color::Red);
    m_checkersButton.setFillColor(sf::Color::White);
    m_exitButton.setFillColor(sf::Color::White);
}
void GameChoice::ActionExitButtonSelected()
{
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