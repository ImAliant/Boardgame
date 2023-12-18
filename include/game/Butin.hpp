#include "../State.hpp"
#include "../UIHandler.hpp"
#include "../Board.hpp"
#include "../Launcher.hpp"
#include "../AssetManager.hpp"
#include "../EventHandler.hpp"

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
namespace butin {
    const int BLACKPIECE_TEXTUREID = 0;
    const int BOARD_SIZE = 8;
    const sf::Color BACKGROUND_COLOR = sf::Color(46, 24, 3);
    const sf::Color BLACKCELL_COLOR = sf::Color(112, 74, 39);
    const sf::Color WHITECELL_COLOR = sf::Color(209, 183, 151);
    const int NB_TEXTURES = 3;
    const int REDPIECE_TEXTUREID = 1;
    const int YELLOWPIECE_TEXTUREID = 2;
}




class Butin: public Engine::State,public UI::UIHandler, public EventHandler
{
    private:
        std::shared_ptr<Context> m_context;

        std ::unique_ptr<Board> m_board;
        std::vector<std::shared_ptr<Player>> m_players;
        std::shared_ptr<Player> m_currentPlayer;
        std::array<sf::Texture, butin::NB_TEXTURES> m_pieceTexture;
        int m_currentPlayerIndex;
         sf::RectangleShape m_boardBackgroud;

        //std::array<sf::Texture, NB_TEXTURES > m_pieceTexture;
        std::array<std::array<sf::RectangleShape, butin::BOARD_SIZE>, butin::BOARD_SIZE> m_boardCell;
        std::array<std::array<sf::RectangleShape, butin::BOARD_SIZE>, butin::BOARD_SIZE> m_boardPiece;

        sf::RectangleShape m_lineSeparator1;
        sf::RectangleShape m_lineSeparator2;

        int m_currentRound = 0;

        sf::Text m_lauchgameButton;
        sf::Text m_exitButton;
        bool m_isGameStarted = false;

        bool m_isPieceSelected = false;
        bool m_pieceCanBeMoved = false;

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
        int selectedPieceX ;
        int selectedPieceY ;

    public :
        explicit Butin(const std::shared_ptr<Context> &context);
        ~Butin() override;

        // state methods who handle the input and update the game window
        void Init() override;
        void ProcessInput() override;
        void Update() override;
        void Draw() override;

        // init methods
        void initPlayers();
        void initPieceTexture();
        void initBoardBackground(float backgroundBoardWidth, float backgroundBoardHeight);
        void initBoardCells(float cellWidth, float cellHeight);
        void initBoardPieces(float pieceWidth, float pieceHeight, float cellWidth, float cellHeight);
        void DrawBoardCells();
        void DrawBoardPieces();

        // ui methods
        void InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize = 30) override;
        void UpdateBoard();
          // event handler methods
        void UpdateButtonHoverState(const sf::Event& event) override;
        void UpdateButtonSelectionState() override;
        void HandleMousePressed(const sf::Event& event) override;
        bool isValidJump(int startX, int startY, int endX, int endY);
        void nextPlayerTurn();
        bool additionalJumpsAvailable(int x, int y);
        void performJump(int startX, int startY, int endX, int endY);
        bool isValidJumpSelected(int startX, int startY, int endX, int endY);    
        sf::RectangleShape& getRectangleShapeAt(int x, int y) ;
        void resetCellAppearance(int x, int y);
        void clearMoveHighlights();
        void highlightCell(int x, int y);
      void showPossibleJumps(int x, int y) ;
        std::vector<std::pair<int, int>> getPossibleMoves(Board& board, int currentX, int currentY);
    bool isYellowPieceSelected(int x, int y);



        void selectYellowPiece(int x, int y);

        void performFirstRoundAction(int x, int y);
        bool isWithinBoard(int x, int y) ;
        void processMouseClick(const sf::Event::MouseButtonEvent &event);
        void doPlayerTurn(const sf::Event::MouseButtonEvent &event);
        void printBoardState();
        void closeWindow() const;
};
