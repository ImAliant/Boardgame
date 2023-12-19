#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Launcher.hpp"
#include "UIHandler.hpp"
#include "EventHandler.hpp"

class MainMenu: public Engine::State, public UI::UIHandler, public EventHandler
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_choiceButton;
        sf::Text m_exitButton;

        bool m_isChoiceButtonSelected = true;
        bool m_isChoiceButtonPressed = false;

        bool m_isExitButtonSelected = false;
        bool m_isExitButtonPressed = false;
    public:
        explicit MainMenu(const std::shared_ptr<Context> &context);
        ~MainMenu() override;

        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;

        void InputUp() override;
        void InputDown() override;
        void InputReturn() override;
        void InputEscape() override;
};