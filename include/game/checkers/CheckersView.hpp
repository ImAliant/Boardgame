#pragma once

#include "../../UIHandler.hpp"
#include "../../Launcher.hpp"
#include "CheckersBoard.hpp"
#include "../../Constants.hpp"
#include "../../Types.hpp"

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
    bool m_isPlayerturnTextVisible = false;
};

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
        void LoadTexture(const int textureID, std::shared_ptr<Context> context);
        void InitBoardBackground();
        void InitBoardCell(const CheckersBoard& board);
        sf::Vector2f CalculatePosition(float offset, const coord_t coord) const;

        void InitBoardPiece(const CheckersBoard& board);
    public:
        CheckersView();
        ~CheckersView() override;

        void Init(std::shared_ptr<Context> context, const CheckersBoard& board);

        void Draw(sf::RenderWindow& window);
        void DrawBoardCells(sf::RenderWindow& window);
        void DrawBoardPiece(sf::RenderWindow& window);
        void UpdateBoard(const CheckersBoard& board);

        void SetupBoardPiece(const coord_t coord, const CheckersBoard &board);
        
        void SetPieceTexture(sf::RectangleShape &piece, char color, bool promoted);

        void HighlightCell(const coord_t coord, const sf::Color color);
        void RemoveHighlightCell(const coord_t coord);
        void HighlightPossibleMoves(const std::vector<coord_t>& possibleMoves);
        void RemoveHighlightPossibleMoves(const std::vector<coord_t>& possibleMoves);

        void Render();

        void PrintCurrentPlayer(std::shared_ptr<Player> currentPlayer) const;
        void PrintWinner(char winner) const;

        coord_t GetBoardCoord(int x, int y) const;

        void UpdateExitSelectedFlag(bool newValue);
        void UpdateLaunchSelectedFlag(bool newValue);
        void UpdateExitHoveredFlag(bool newValue);
        void UpdateLaunchHoveredFlag(bool newValue);

        void HideLaunchgameButton();
        void NeedHighlight();
        void RemoveHighlight();
        void LauchButtonPressed();
        void ExitButtonPressed();

        void ResetLaunchPressedFlag();

        // getters
        sf::Text& GetLaunchgameButton();
        sf::Text& GetExitButton();

        // getters for boolean flags
        bool IsLaunchgameButtonSelected() const;
        bool IsLaunchgameButtonPressed() const;
        bool IsLaunchgameButtonVisible() const;
        bool IsExitButtonSelected() const;
        bool IsExitButtonPressed() const;
        bool HasHighLightedCell() const;
};