#pragma once

#include "../UIHandler.hpp"
#include "../Launcher.hpp"
#include "../Board.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class CheckersView: public UI::UIHandler
{
    private:
        const sf::Color BLACKCELL_COLOR = sf::Color{112, 74, 39};
        const sf::Color WHITECELL_COLOR = sf::Color{209, 183, 151};
        const sf::Color BOARDBACKGROUND_COLOR = sf::Color{46, 24, 3};
        const sf::Vector2f BOARDBACKGROUND_SIZE = 
            sf::Vector2f{static_cast<float>(WINDOW_SIZE.x) - 10.f, 
                         static_cast<float>(WINDOW_SIZE.y) - 110.f};
        const sf::Vector2f BOARDBACKGROUND_POSITION = sf::Vector2f{5.f, 5.f};
        const sf::Vector2f BOARDCELL_SIZE = 
            sf::Vector2f{(BOARDBACKGROUND_SIZE.x - 10.f) / static_cast<float>(10),  // TODO: BOARD_SIZE
                         (BOARDBACKGROUND_SIZE.y - 10.f) / static_cast<float>(10)};
        const sf::Vector2f BOARDPIECE_SIZE =
            sf::Vector2f{BOARDCELL_SIZE.x - 10.f, BOARDCELL_SIZE.y - 10.f};
        const sf::Vector2f BOARDOFFSET = sf::Vector2f{10.f, 10.f};

        sf::RectangleShape m_boardBackgroud;

        std::vector<sf::Texture> m_pieceTexture;

        std::vector<std::vector<sf::RectangleShape>> m_boardCell;
        std::vector<std::vector<sf::RectangleShape>> m_boardPiece;

        sf::RectangleShape m_lineSeparator1;

        sf::Text m_lauchgameButton;
        sf::Text m_exitButton;

        // boolean flags related to UI state
        bool m_boardNeedUpdate = false;
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
    public:
        CheckersView();
        ~CheckersView() override;

        void Init(std::shared_ptr<Context> context, const Board& board);

        void InitPieceTexture(std::shared_ptr<Context> context);
        void InitBoardBackground();
        void InitBoardCell(const Board& board);
        void InitBoardPiece(const Board& board);

        void Draw(sf::RenderWindow& window);
        void DrawBoardCells(sf::RenderWindow& window);
        void DrawBoardPiece(sf::RenderWindow& window);

        void HighlightCell(std::pair<int, int> coord, sf::Color color);
        void RemoveHighlightCell(std::pair<int, int> coord);
        void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);
        void RemoveHighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);

        void HideLaunchgameButton();
        void RenderButton();

        std::pair<int, int> GetBoardCoord(int x, int y/*, const sf::RenderWindow& window*/) const;

        void UpdateFlag(bool& flagToUpdate, bool newValue) const;

        // getters
        sf::Text& GetLaunchgameButton();
        sf::Text& GetExitButton();
        std::vector<std::vector<sf::RectangleShape>>& GetBoardCell();
        // getters for boolean flags
        bool& GetBoardNeedUpdate();
        bool& GetIsLaunchgameButtonSelected();
        bool& GetIsLaunchgameButtonPressed();
        bool& GetIsLaunchgameButtonHovered();
        bool& GetWasLaunchgameButtonHovered();
        bool& GetIsLaunchgameButtonVisible();
        bool& GetIsExitButtonSelected();
        bool& GetIsExitButtonPressed();
        bool& GetIsExitButtonHovered();
        bool& GetWasExitButtonHovered();
        bool& GetHasHighLightedCell();
};