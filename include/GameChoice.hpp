#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Launcher.hpp"
#include "UI.hpp"
#include "InputHandler.hpp"

class GameChoice: public Engine::State, public UI::UIInitializer, public InputHandler
{
    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_butinButton;
        sf::Text m_checkersButton;
        sf::Text m_bulltrickerButton;
        sf::Text m_exitButton;

        bool m_isButinButtonSelected = true;
        bool m_isButinButtonPressed = false;

        bool m_isCheckersButtonSelected = false;
        bool m_isCheckersButtonPressed = false;

        bool m_isBulltrickerButtonSelected = false;
        bool m_isBulltrickerButtonPressed = false;

        bool m_isExitButtonSelected = false;
        bool m_isExitButtonPressed = false;
    public:
        explicit GameChoice(const std::shared_ptr<Context> &context);
        ~GameChoice() override;

        void Init() override;
        void ProcessInput() override;
        void Update() override;
        
        void Draw() override;

        void InputUp() override;
        void InputDown() override;
        void InputReturn() override;
        void InputEscape() override;

        void ActionButinButtonSelected();
        void ActionCheckersButtonSelected();
        void ActionBulltrickerButtonSelected();
        void ActionExitButtonSelected();
        void resetButtonValues();

        void InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize = 30) override;
};