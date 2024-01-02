#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Launcher.hpp"
#include "UIHandler.hpp"
#include "EventHandler.hpp"
#include "Button.hpp"

class GameChoice: public Engine::State, public UIHandler, public EventHandler
{
    private:
        std::shared_ptr<Context> m_context;

        sf::RectangleShape m_background;

        std::array<sf::Text, GameChoiceConstants::NUMBER_OF_TEXTS> m_texts;
        std::array<std::unique_ptr<Button>, 
                   GameChoiceConstants::NUMBER_OF_BUTTONS> m_buttons;

        void UpdateButtonHoverState(const sf::Event& event) override;
        void UpdateButtonSelectionState() override;
        void HandleMousePressed(const sf::Event& event) override;
        void UpdateButtonPushed() override;

        void InitButton(size_t buttonID, const std::string& text, 
                        const sf::Vector2f& position, const sf::Font& font, 
                        const std::function<void()>& action);

        template <typename T>
        void CheckAssets(T const* ptr, const std::string& errorMessage) const;
    public:
        explicit GameChoice(const std::shared_ptr<Context> &context);
        ~GameChoice() override = default;

        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;
};