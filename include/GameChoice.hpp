#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Launcher.hpp"
#include "UIHandler.hpp"
#include "EventHandler.hpp"
#include "GameChoiceFlags.hpp"

class GameChoice: public Engine::State, public UI::UIHandler, public EventHandler
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_butinButton;
        sf::Text m_checkersButton;
        sf::Text m_bulltrickerButton;
        sf::Text m_exitButton;

        GameChoiceFlags m_flags;
    public:
        explicit GameChoice(const std::shared_ptr<Context> &context);
        ~GameChoice() override = default;

        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;

        void UpdateButtonHoverState(const sf::Event& event) override;
        void UpdateButtonSelectionState() override;
        void HandleMousePressed(const sf::Event& event) override;
        void UpdateButtonPushed() override;

        void CloseWindow() const;
};