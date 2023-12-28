#pragma once

#include "../../UIHandler.hpp"
#include "../../Launcher.hpp"
#include "ButinBoard.hpp"
#include "../../Constants.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

struct Butin_flagsview_t {
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

class ButinView: public UI::UIHandler
{
    private:
        sf::RectangleShape m_boardBackgroud;

        std::vector<sf::Texture> m_pieceTexture;

        std::vector<std::vector<sf::RectangleShape>> m_boardCell;
        std::vector<std::vector<sf::RectangleShape>> m_boardPiece;

        sf::RectangleShape m_lineSeparator;

        sf::Text m_lauchgameButton;
        sf::Text m_exitButton;

        Butin_flagsview_t m_flags;

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

        void PrintCurrentPlayer(std::shared_ptr<Player> currentPlayer) const;

        std::pair<int, int> GetBoardCoord(int x, int y) const;

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
        void printWinner(Player* winner)const;
        void printScore(int score) const;

};