#pragma once

#include "../../State.hpp"
#include "../../UIHandler.hpp"
#include "../../Launcher.hpp"
#include "../../AssetManager.hpp"
#include "../../EventHandler.hpp"
#include "../../Constants.hpp"
#include "Butin.hpp"
#include "ButinView.hpp"

#include <memory>
#include <vector>

class ButinController: public Engine::State, public EventHandler 
{
    private:
        std::shared_ptr<Context> m_context;
        std::unique_ptr<Butin> m_model;
        std::unique_ptr<ButinView> m_view;

        void Start();
        void End();

        // Event handling
        void UpdateButtonHoverState(const sf::Event& event) override;
        void UpdateButtonSelectionState() override;
        void HandleMousePressed(const sf::Event& event) override;
        
        // Update methods
        void UpdateHighlight() const;
        void UpdateBoard() const;
        void UpdateCurrentPlayer() const;
        void UpdateButtonPushed();

        void HighlightSelectedPiece() const;
        void RemoveHighlightSelectedPiece() const;

        void CloseWindow() const;
        void CloseGame() const;
    public:
        explicit ButinController(std::shared_ptr<Context> context);
        ~ButinController() override;

        // State handling
        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;
};