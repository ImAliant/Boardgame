#pragma once

#include "../State.hpp"
#include "../UI.hpp"
#include "../Board.hpp"
#include "../Launcher.hpp"
#include "../AssetManager.hpp"

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

const int NB_TEXTURES = 2;
const int BLACKPIECE_TEXTUREID = 0;
const int WHITEPIECE_TEXTUREID = 1;

const int BOARD_SIZE = 10;
const sf::Color BACKGROUND_COLOR = sf::Color(46, 24, 3);
const sf::Color BLACKCELL_COLOR = sf::Color(112, 74, 39);
const sf::Color WHITECELL_COLOR = sf::Color(209, 183, 151);

class Checkers : public Engine::State, public UI::UIInitializer
{
    private:
        std::shared_ptr<Context> m_context;

        // data structure
        std::unique_ptr<Board> m_board;
        std::vector<std::shared_ptr<Player>> m_players;

        // game logic
        std::shared_ptr<Player> m_currentPlayer;

        // ui
        sf::RectangleShape m_boardBackgroud;

        std::array<sf::Texture, NB_TEXTURES> m_pieceTexture;
        std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> m_boardCell;
        std::array<std::array<sf::RectangleShape, BOARD_SIZE>, BOARD_SIZE> m_boardPiece;

        sf::RectangleShape m_lineSeparator1;
        sf::RectangleShape m_lineSeparator2;

        sf::Text m_lauchgameButton;
        sf::Text m_exitButton;

        // boolean
        bool m_isLaunchgameButtonSelected = false;
        bool m_isLaunchgameButtonPressed = false;
        bool m_isLaunchgameButtonHovered = false;
        bool m_wasLaunchgameButtonHovered = false;

        bool m_isExitButtonSelected = false;
        bool m_isExitButtonPressed = false;
        bool m_isExitButtonHovered = false;
        bool m_wasExitButtonHovered = false;
    public:
        explicit Checkers(const std::shared_ptr<Context> &context);
        ~Checkers() override;

        // state methods who handle the input and update the game window
        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;
        void Start() override;

        // game methods
        void startGame();
        void movePiece(const sf::Vector2i &position);
        void selectPiece(const sf::Vector2i &position);
        void deselectPiece(const sf::Vector2i &position);
        void movePieceTo(const sf::Vector2i &position);
        void removePiece(const sf::Vector2i &position);
        void promotePiece(const sf::Vector2i &position);
        void checkForWin();
        void switchPlayer();
        void updatePossibleMoves() const;

        // init methods
        void initPlayers();
        void initPieceTexture();
        void initBoardBackground(float backgroundBoardWidth, float backgroundBoardHeight);
        void initBoardCells(float cellWidth, float cellHeight);
        void initBoardPieces(float pieceWidth, float pieceHeight, float cellWidth, float cellHeight);

        void DrawBoardCells();
        void DrawBoardPieces();

        void InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize = 30) override;
};