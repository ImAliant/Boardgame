#pragma once

#include "../../UIHandler.hpp"
#include "../../Launcher.hpp"
#include "ButinBoard.hpp"
#include "../../Constants.hpp"
#include "../ViewFlags.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class ButinView: public UI::UIHandler
{
    private:
        sf::RectangleShape m_boardBackgroud;

        std::vector<sf::Texture> m_pieceTexture;

        std::vector<std::vector<sf::RectangleShape>> m_boardCell;
        std::vector<std::vector<sf::RectangleShape>> m_boardPiece;

        sf::RectangleShape m_lineSeparator;

        sf::Text m_lauchgameButton;
        sf::Text m_menuButton;

        ViewFlags m_flags;

        void InitPieceTexture(std::shared_ptr<Context> context);
        void LoadTexture(int textureID, std::shared_ptr<Context> context);
        void InitBoardBackground();
        void InitBoardCell(const ButinBoard& board);
        sf::Vector2f CalculatePosition(float offset, coord_t coord) const;

        void InitBoardPiece(const ButinBoard& board);
    public:
        ButinView();
        ~ButinView() override;

        void Init(std::shared_ptr<Context> context, const ButinBoard& board);

        void Draw(sf::RenderWindow& window);
        void DrawBoardCells(sf::RenderWindow& window);
        void DrawBoardPiece(sf::RenderWindow& window);
        void UpdateBoard(const ButinBoard& board);

        void SetupBoardPiece(const coord_t coord, const ButinBoard &board);
        
        void SetPieceTexture(sf::RectangleShape &piece, char color);

        void HighlightCell(std::pair<int, int> coord, sf::Color color);
        void RemoveHighlightCell(std::pair<int, int> coord);
        void HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);
        void RemoveHighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves);

        void Render();

        void PrintTurn(const std::shared_ptr<Player> currentPlayer, const std::vector<std::shared_ptr<Player>>& players) const;
        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const;
        void PrintPlayersScore(const std::vector<std::shared_ptr<Player>>& players) const;
        void PrintWinner(const Player* winner)const;
        void PrintScore(const int score) const;

        std::pair<int, int> GetBoardCoord(int x, int y) const;

        void UpdateMenuSelectedFlag(bool newValue);
        void UpdateLaunchSelectedFlag(bool newValue);
        void UpdateMenuHoveredFlag(bool newValue);
        void UpdateLaunchHoveredFlag(bool newValue);

        void HideLaunchgameButton();
        void NeedHighlight();
        void RemoveHighlight();
        void LauchButtonPressed();
        void MenuButtonPressed();

        void ResetLaunchPressedFlag();

        // getters
        sf::Text& GetLaunchgameButton();
        sf::Text& GetMenuButton();

        // getters for boolean flags
        bool& IsLaunchgameButtonSelected();
        bool& IsLaunchgameButtonPressed();
        bool& IsLaunchgameButtonVisible();
        bool& IsMenuButtonSelected();
        bool& IsMenuButtonPressed();
        bool& HasHighLightedCell();
};