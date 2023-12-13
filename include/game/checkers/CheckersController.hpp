#pragma once

#include "../../State.hpp"
#include "../../UIHandler.hpp"
#include "../../Launcher.hpp"
#include "../../AssetManager.hpp"
#include "../../EventHandler.hpp"
#include "../../Constants.hpp"
#include "Checkers.hpp"
#include "CheckersView.hpp"

#include <memory>
#include <vector>

class CheckersController: public Engine::State, public EventHandler 
{
    private:
        std::shared_ptr<Context> m_context;
        std::unique_ptr<Checkers> m_model;
        std::unique_ptr<CheckersView> m_view;

        void Start();
        void End();

        // Event handling
        void UpdateButtonHoverState(const sf::Event& event) override;
        void UpdateButtonSelectionState() override;
        void HandleMousePressed(const sf::Event& event) override;
        
        void CloseWindow() const;
    public:
        explicit CheckersController(std::shared_ptr<Context> context);
        ~CheckersController() override;

        // State handling
        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;
};