#pragma once

#include "ViewFlags.hpp"
#include "../Board.hpp"
#include "../UIHandler.hpp"
#include "../Constants.hpp"
#include "../Launcher.hpp"
#include "../Types.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class View: public UI::UIHandler
{
    protected:
        sf::RectangleShape m_boardBackground;

        std::vector<sf::Texture> m_pieceTexture;

        std::vector<std::vector<sf::RectangleShape>> m_boardCell;
        std::vector<std::vector<sf::RectangleShape>> m_boardPiece;

        sf::RectangleShape m_lineSeparator;

        sf::Text m_lauchgameButton;
        sf::Text m_menuButton;

        ViewFlags m_flags;

        void InitBase(std::shared_ptr<Context> context, const Board& board, const std::vector<int>& textureIDs, const sf::Vector2f piecesize, const sf::Vector2f cellsize);
        
        void InitPieceTexture(const std::shared_ptr<Context> context, const std::vector<int>& textureIDs);
        void LoadTexture(const int textureID, const std::shared_ptr<Context> context);
        void InitBoardBackground();
        void InitBoardCell(const Board& board, const sf::Vector2f cellsize);
        void InitBoardPiece(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize);
        virtual void SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize);
        sf::Vector2f CalculatePosition(const float offset, const coord_t coord, const sf::Vector2f cellsize) const;

        void DrawBoardCells(sf::RenderWindow& window);
        void DrawBoardPiece(sf::RenderWindow& window);

        void UpdateBoardBase(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize);

        virtual void SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted) = 0;

        coord_t GetBoardCoordBase(const int x, const int y, const sf::Vector2f cellsize) const;

        bool IsLaunchgameButtonVisible() const;
    public:
        View();
        ~View() override;

        virtual void Init(std::shared_ptr<Context> context, const Board& board) = 0;
        virtual void UpdateBoard(const Board& board) = 0;

        void Draw(sf::RenderWindow& window);
        void HighlightCell(const coord_t coord, const sf::Color color);
        void RemoveHighlightCell(const coord_t coord);
        void HighlightPossibleMoves(const std::vector<coord_t>& possibleMoves);
        void RemoveHighlightPossibleMoves(const std::vector<coord_t>& possibleMoves);
        void Render();

        void UpdateMenuSelectedFlag(const bool newValue);
        void UpdateLaunchSelectedFlag(const bool newValue);
        void UpdateMenuHoveredFlag(const bool newValue);
        void UpdateLaunchHoveredFlag(const bool newValue);

        void HideLaunchgameButton();
        void NeedHighlight();
        void RemoveHighlight();
        void LauchButtonPressed();
        void MenuButtonPressed();

        void ResetLaunchPressedFlag();

        virtual coord_t GetBoardCoord(const int x, const int y) const = 0;

        virtual void PrintWinner(const Player* winner) const = 0;
        virtual void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const = 0;

        // getters
        sf::Text& GetLaunchgameButton();
        sf::Text& GetMenuButton();

        // getters for boolean flags
        bool IsLaunchgameButtonSelected() const;
        bool IsLaunchgameButtonPressed() const;
        bool IsMenuButtonSelected() const;
        bool IsMenuButtonPressed() const;
        bool HasHighLightedCell() const;
};