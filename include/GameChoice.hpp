#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Launcher.hpp"
#include "UIHandler.hpp"
#include "EventHandler.hpp"

class GameChoice: public Engine::State, public UI::UIHandler//, public EventHandler
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_butinButton;
        sf::Text m_checkersButton;
        sf::Text m_bulltrickerButton;
        sf::Text m_exitButton;

        bool m_isButinButtonHovered = false;
        bool m_wasButinButtonHovered = false;
        bool m_isButinButtonSelected = false;
        bool m_isButinButtonPressed = false;

        bool m_isCheckersButtonHovered = false;
        bool m_wasCheckersButtonHovered = false;
        bool m_isCheckersButtonSelected = false;
        bool m_isCheckersButtonPressed = false;

        bool m_isBulltrickerButtonHovered = false;
        bool m_wasBulltrickerButtonHovered = false;
        bool m_isBulltrickerButtonSelected = false;
        bool m_isBulltrickerButtonPressed = false;

        bool m_isExitButtonHovered = false;
        bool m_wasExitButtonHovered = false;
        bool m_isExitButtonSelected = false;
        bool m_isExitButtonPressed = false;
    public:
        explicit GameChoice(const std::shared_ptr<Context> &context);
        ~GameChoice() override = default;

        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;

        void UpdateButtonHoverState(const sf::Event& event);
        void UpdateButtonSelectionState();
        void HandleMousePressed(const sf::Event& event);
        void UpdateButtonPushed();

        void CloseWindow() const;
};