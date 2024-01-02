#include "../include/GameChoice.hpp"
#include "../include/game/checkers/CheckersController.hpp"
#include "../include/game/butin/ButinController.hpp"
#include "../include/game/bulltricker/BulltrickerController.hpp"
#include "../include/Constants.hpp"

#include <iostream>
#include <algorithm>
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

    InitRectangleShape(m_background, sf::Vector2f(static_cast<float>(WindowConstants::WINDOW_SIZE.x), static_cast<float>(WindowConstants::WINDOW_SIZE.y)), sf::Vector2f(0.f, 0.f));
    sf::Texture const* background = &m_context->m_assets->GetTexture(MENUBACKGROUND);
    if (!background)
    {
        throw std::runtime_error("MainMenu::Init() : background is nullptr");
    }
    m_background.setTexture(background);

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
    struct ButtonState
    {
        sf::Text& m_button;
        bool& m_isSelected;
        bool& m_isHovered;
        bool& m_wasHovered;
    };

    std::array<ButtonState, 4> buttons = {
        ButtonState{m_butinButton, m_flags.m_isButinButtonSelected, m_flags.m_isButinButtonHovered, m_flags.m_wasButinButtonHovered},
        ButtonState{m_checkersButton, m_flags.m_isCheckersButtonSelected, m_flags.m_isCheckersButtonHovered, m_flags.m_wasCheckersButtonHovered},
        ButtonState{m_bulltrickerButton, m_flags.m_isBulltrickerButtonSelected, m_flags.m_isBulltrickerButtonHovered, m_flags.m_wasBulltrickerButtonHovered},
        ButtonState{m_exitButton, m_flags.m_isExitButtonSelected, m_flags.m_isExitButtonHovered, m_flags.m_wasExitButtonHovered}
    };

    for (const auto& button : buttons)
    {
        UpdateButtonState(button.m_button, button.m_isSelected, button.m_isHovered, button.m_wasHovered);
    }

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
    struct ButtonHoverState
    {
        sf::Text& m_button;
        bool& m_isHovered;
    };

    std::array<ButtonHoverState, 4> buttons = {
        ButtonHoverState{m_butinButton, m_flags.m_isButinButtonHovered},
        ButtonHoverState{m_checkersButton, m_flags.m_isCheckersButtonHovered},
        ButtonHoverState{m_bulltrickerButton, m_flags.m_isBulltrickerButtonHovered},
        ButtonHoverState{m_exitButton, m_flags.m_isExitButtonHovered}
    };

    for (const auto& button : buttons)
        button.m_isHovered = IsButtonHovered(button.m_button, event);
}
void GameChoice::UpdateButtonSelectionState()
{
    struct ButtonSelectionState
    {
        sf::Text& m_button;
        bool& m_isSelected;
    };

    std::array<ButtonSelectionState, 4> buttons = {
        ButtonSelectionState{m_butinButton, m_flags.m_isButinButtonSelected},
        ButtonSelectionState{m_checkersButton, m_flags.m_isCheckersButtonSelected},
        ButtonSelectionState{m_bulltrickerButton, m_flags.m_isBulltrickerButtonSelected},
        ButtonSelectionState{m_exitButton, m_flags.m_isExitButtonSelected}
    };

    for (const auto& button : buttons)
        button.m_isSelected = IsButtonSelected(button.m_button, *m_context->m_window);
}
void GameChoice::HandleMousePressed(const sf::Event& event)
{
    struct ButtonPressedState
    {
        bool& m_isSelected;
        bool& m_isPressed;
    };

    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;

    if (isMousePressed)
    {
        std::array<ButtonPressedState, 4> buttons = {
            ButtonPressedState{m_flags.m_isButinButtonSelected, m_flags.m_isButinButtonPressed},
            ButtonPressedState{m_flags.m_isCheckersButtonSelected, m_flags.m_isCheckersButtonPressed},
            ButtonPressedState{m_flags.m_isBulltrickerButtonSelected, m_flags.m_isBulltrickerButtonPressed},
            ButtonPressedState{m_flags.m_isExitButtonSelected, m_flags.m_isExitButtonPressed}
        };

        std::find_if(buttons.begin(), buttons.end(), [](const auto& button) { return button.m_isSelected; })->m_isPressed = true;
    }
}
void GameChoice::UpdateButtonPushed()
{
    if (m_flags.m_isButinButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<ButinController>(m_context), true);
        m_flags.m_isButinButtonPressed = false;
    }
    else if (m_flags.m_isCheckersButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<CheckersController>(m_context), true);
        m_flags.m_isCheckersButtonPressed = false;
    }
    else if (m_flags.m_isBulltrickerButtonPressed)
    {
        std::cout << "Bulltricker" << std::endl;
        m_context->m_states->Add(std::make_unique<BulltrickerController>(m_context), true);
        m_flags.m_isBulltrickerButtonPressed = false;
    }
    else if (m_flags.m_isExitButtonPressed)
    {
        CloseWindow();
    }
}

void GameChoice::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->draw(m_background);

    std::array buttons = {
        m_gameTitle,
        m_butinButton,
        m_checkersButton,
        m_bulltrickerButton,
        m_exitButton
    };
    for (const auto& button : buttons)
        m_context->m_window->draw(button);

    m_context->m_window->display();
}

void GameChoice::CloseWindow() const
{
    m_context->m_states->PopAll();
    m_context->m_window->close();
}