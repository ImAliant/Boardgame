#pragma once

#include "../../UIHandler.hpp"
#include "../../Launcher.hpp"
#include "../../CheckersBoard.hpp"
#include "../../Constants.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

struct flagsview_t {
    bool m_isLaunchgameButtonSelected = false;
    bool m_isLaunchgameButtonPressed = false;
    bool m_isLaunchgameButtonHovered = false;
    bool m_wasLaunchgameButtonHovered = false;
    bool m_isLaunchgameButtonVisible = true;
    bool m_isExitButtonSelected = false;
    bool m_isExitButtonPressed = false;
    bool m_isExitButtonHovered = false;
    bool m_wasExitButtonHovered = false;
    bool m_hasHighLightedCell = false;
};

/*struct button_t {
    sf::Text m_text;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Color m_color;
    sf::Color m_hoverColor;
    sf::Color m_selectedColor;
    sf::Color m_pressedColor;
    sf::Color m_textColor;
    sf::Color m_textHoverColor;
    sf::Color m_textSelectedColor;
    sf::Color m_textPressedColor;
    bool m_isSelected = false;
    bool m_isPressed = false;
    bool m_isHovered = false;
    bool m_wasHovered = false;
    bool m_isVisible = true;
};*/

class CheckersView: public UI::UIHandler
{
    private:
        sf::RectangleShape m_boardBackgroud;

        std::vector<sf::Texture> m_pieceTexture;

        std::vector<std::vector<sf::RectangleShape>> m_boardCell;
        std::vector<std::vector<sf::RectangleShape>> m_boardPiece;

        sf::RectangleShape m_lineSeparator;

        sf::Text m_lauchgameButton;
        sf::Text m_exitButton;

        flagsview_t m_flags;

        void InitPieceTexture(std::shared_ptr<Context> context);
        void LoadTexture(int textureID, std::shared_ptr<Context> context);

        void InitBoardBackground();
        void InitBoardCell(const CheckersBoard& board);
        sf::Vector2f CalculatePosition(float offset, int i, int j) const;

        void InitBoardPiece(const CheckersBoard& board);
    public:
        CheckersView();
        ~CheckersView() override;

        void Init(std::shared_ptr<Context> context, const CheckersBoard& board);

        void Draw(sf::RenderWindow& window);
        void DrawBoardCells(sf::RenderWindow& window);
        void DrawBoardPiece(sf::RenderWindow& window);
        void UpdateBoard(const CheckersBoard& board);

        void HighlightCell(std::pair<int, int> coord, sf::Color color);
        void RemoveHighlightCell(std::pair<int, int> coord);
        void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);
        void RemoveHighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);

        void HideLaunchgameButton();
        void RenderButton();

        std::pair<int, int> GetBoardCoord(int x, int y) const;

        void UpdateFlag(bool& flagToUpdate, bool newValue) const;

        // getters
        sf::Text& GetLaunchgameButton();
        sf::Text& GetExitButton();
        std::vector<std::vector<sf::RectangleShape>>& GetBoardCell();

        // getters for boolean flags
        bool& IsLaunchgameButtonSelected();
        bool& IsLaunchgameButtonPressed();
        bool& IsLaunchgameButtonHovered();
        bool& WasLaunchgameButtonHovered();
        bool& IsLaunchgameButtonVisible();
        bool& IsExitButtonSelected();
        bool& IsExitButtonPressed();
        bool& IsExitButtonHovered();
        bool& WasExitButtonHovered();
        bool& HasHighLightedCell();
};