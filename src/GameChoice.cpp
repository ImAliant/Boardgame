#include "../include/GameChoice.hpp"
#include "../include/game/checkers/CheckersController.hpp"
#include "../include/game/butin/ButinController.hpp"
#include "../include/Constants.hpp"

#include <iostream>
#include <SFML/Window/Event.hpp>

GameChoice::GameChoice(const std::shared_ptr<Context> &context): m_context(context) {}

void GameChoice::Init() 
{
    using namespace UIConstants;
    using namespace UIConstants::GameChoiceContext;

    sf::Font const* font = &m_context->m_assets->GetFont(MAIN_FONT);
    if (!font)
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
    UpdateButtonState(m_butinButton, m_isButinButtonSelected, m_isButinButtonHovered, m_wasButinButtonHovered);
    UpdateButtonState(m_checkersButton, m_isCheckersButtonSelected, m_isCheckersButtonHovered, m_wasCheckersButtonHovered);
    UpdateButtonState(m_bulltrickerButton, m_isBulltrickerButtonSelected, m_isBulltrickerButtonHovered, m_wasBulltrickerButtonHovered);
    UpdateButtonState(m_exitButton, m_isExitButtonSelected, m_isExitButtonHovered, m_wasExitButtonHovered);

    UpdateButtonPushed();
}

void GameChoice::ProcessInput()
{
    sf::Event event;

    while (m_context->m_window->pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed)
        {
            CloseWindow();
        }

        UpdateButtonHoverState(event);

        if (event.type == sf::Event::MouseMoved)
        {
            UpdateButtonSelectionState();
        }
        else if (event.type == sf::Event::MouseButtonPressed) 
        {
            HandleMousePressed(event);
        }
    }
}

void GameChoice::UpdateButtonHoverState(const sf::Event& event)
{
    bool isButinHovered = m_butinButton.getGlobalBounds().contains(
        static_cast<float>(event.mouseButton.x), 
        static_cast<float>(event.mouseButton.y)
    );
    bool isCheckersHovered = m_checkersButton.getGlobalBounds().contains(
        static_cast<float>(event.mouseButton.x), 
        static_cast<float>(event.mouseButton.y)
    );
    bool isBulltrickerHovered = m_bulltrickerButton.getGlobalBounds().contains(
        static_cast<float>(event.mouseButton.x), 
        static_cast<float>(event.mouseButton.y)
    );
    bool isExitHovered = m_exitButton.getGlobalBounds().contains(
        static_cast<float>(event.mouseButton.x), 
        static_cast<float>(event.mouseButton.y)
    );
    
    m_isButinButtonHovered = isButinHovered;
    m_isCheckersButtonHovered = isCheckersHovered;
    m_isBulltrickerButtonHovered = isBulltrickerHovered;
    m_isExitButtonHovered = isExitHovered;
}
void GameChoice::UpdateButtonSelectionState()
{
    bool isButinSelected = m_butinButton.getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x), 
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y)
    );
    bool isCheckersSelected = m_checkersButton.getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x), 
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y)
    );
    bool isBulltrickerSelected = m_bulltrickerButton.getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x), 
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y)
    );
    bool isExitSelected = m_exitButton.getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x), 
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y)
    );
    
    m_isButinButtonSelected = isButinSelected;
    m_isCheckersButtonSelected = isCheckersSelected;
    m_isBulltrickerButtonSelected = isBulltrickerSelected;
    m_isExitButtonSelected = isExitSelected;
}
void GameChoice::HandleMousePressed(const sf::Event& event)
{
    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;

    if (isMousePressed)
    {
        if (m_isButinButtonSelected)
        {
            m_isButinButtonPressed = true;
        }
        else if (m_isCheckersButtonSelected)
        {
            m_isCheckersButtonPressed = true;
        }
        else if (m_isBulltrickerButtonSelected)
        {
            m_isBulltrickerButtonPressed = true;
        }
        else if (m_isExitButtonSelected)
        {
            m_isExitButtonPressed = true;
        }
    }
}
void GameChoice::UpdateButtonPushed()
{
    if (m_isButinButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<ButinController>(m_context), true);
        m_isButinButtonPressed = false;
    }
    else if (m_isCheckersButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<CheckersController>(m_context), true);
        m_isCheckersButtonPressed = false;
    }
    else if (m_isBulltrickerButtonPressed)
    {
        std::cout << "Bulltricker" << std::endl;
        m_isBulltrickerButtonPressed = false;
    }
    else if (m_isExitButtonPressed)
    {
        CloseWindow();
    }
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

void GameChoice::CloseWindow() const
{
    m_context->m_states->PopAll();
    m_context->m_window->close();
}