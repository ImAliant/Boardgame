#include "../../../include/game/butin/ButinView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace GameConstants::ButinConstants;
using namespace UIConstants;

ButinView::ButinView() {}

ButinView::~ButinView() {}

void ButinView::Init(std::shared_ptr<Context> context, const ButinBoard& board)
{
    InitPieceTexture(context);
    InitBoardBackground();
    InitBoardCell(board);
    InitBoardPiece(board);

    sf::Font const* font = &context->m_assets->GetFont(MAIN_FONT);
    if (font == nullptr)
    {
        std::cout << "The font of is not loaded" << std::endl;
        return;
    }

    InitRectangleShape(m_lineSeparator, GameContext::LINESEPARATOR_SIZE, GameContext::LINESEPARATOR_POSITION);

    InitText(m_lauchgameButton, "Lancer la partie", GameContext::LAUNCHBUTTON_POSITION, *font, CHARACTER_SIZE);
    InitText(m_menuButton, "Menu", GameContext::MENUBUTTON_POSITION, *font, CHARACTER_SIZE);
}

void ButinView::PrintTurn(const std::shared_ptr<Player> currentPlayer, const std::vector<std::shared_ptr<Player>>& players) const
{
    system("clear");
    PrintCurrentPlayer(currentPlayer);
    PrintPlayersScore(players);
}

void ButinView::PrintCurrentPlayer(std::shared_ptr<Player> currentPlayer) const
{
    std::cout << "Current player: " << currentPlayer->ToString() << std::endl;
}

void ButinView::PrintPlayersScore(const std::vector<std::shared_ptr<Player>>& players) const
{
    for (const auto& player : players) {
        PrintScore(player->GetScore());
    }
}

void ButinView::InitPieceTexture(std::shared_ptr<Context> context)
{
    try 
    {
        LoadTexture(BUTIN_YELLOW_PIECE, context);
        LoadTexture(BUTIN_RED_PIECE, context);
        LoadTexture(BUTIN_BLACK_PIECE, context);
        LoadTexture(EMPTY_ASSET, context);
    }
    catch (AssetNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void ButinView::LoadTexture(int textureID, std::shared_ptr<Context> context) 
{
    if (!context->m_assets->HasTexture(textureID)) {
        throw AssetNotFoundException("Texture not found" + std::to_string(textureID));
    }

    m_pieceTexture.push_back(context->m_assets->GetTexture(textureID));
}

void ButinView::InitBoardBackground()
{
    InitRectangleShape(
        m_boardBackgroud, 
        GameConstants::BOARDBACKGROUND_SIZE, 
        GameConstants::BOARDBACKGROUND_POSITION
    );
    m_boardBackgroud.setFillColor(GameConstants::BOARDBACKGROUND_COLOR);
}

void ButinView::InitBoardCell(const ButinBoard& board)
{
    auto rows = board.GetRows();
    auto cols = board.GetCols();

    m_boardCell.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardCell[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            const auto coord = std::make_pair(i, j);

            InitRectangleShape(
                m_boardCell[i][j],
                BOARDCELL_SIZE,
                CalculatePosition(10.f, coord)
            );

            if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(GameConstants::WHITECELL_COLOR);
            else m_boardCell[i][j].setFillColor(GameConstants::BLACKCELL_COLOR);
        }
    }
}

void ButinView::InitBoardPiece(const ButinBoard& board)
{   
    auto rows = board.GetRows();
    auto cols = board.GetCols();

    m_boardPiece.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardPiece[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            const auto coord = std::make_pair(i, j);

            SetupBoardPiece(coord, board);
        }
    }
}
void ButinView::UpdateBoard(const ButinBoard& board)
{
    auto rows = m_boardPiece.size();
    auto cols = m_boardPiece[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const auto coord = std::make_pair(i, j);

            SetupBoardPiece(coord, board);
        }
    }
}

void ButinView::SetupBoardPiece(const coord_t coord, const ButinBoard &board)
{
    const auto& [i, j] = coord;

    InitRectangleShape(
        m_boardPiece[i][j],
        BOARDPIECE_SIZE,
        CalculatePosition(15.f, coord)
    );

    auto piece = board.GetValueAt(coord);
    if (piece != nullptr)
        SetPieceTexture(m_boardPiece[i][j], piece->GetSymbol());
    else
        SetPieceTexture(m_boardPiece[i][j], EMPTY_ID);
}

void ButinView::SetPieceTexture(sf::RectangleShape &piece, char color)
{  
    if (color == GameConstants::ButinConstants::BUTIN_YELLOW)
        piece.setTexture(&m_pieceTexture[YELLOW_PAWN_ID]);
    else if (color == GameConstants::ButinConstants::BUTIN_RED)
        piece.setTexture(&m_pieceTexture[RED_PAWN_ID]);
    else if (color == GameConstants::ButinConstants::BUTIN_BLACK)
        piece.setTexture(&m_pieceTexture[BLACK_PAWN_ID]);
    else 
        piece.setTexture(&m_pieceTexture[EMPTY_ID]);
}

sf::Vector2f ButinView::CalculatePosition(float offset, coord_t coord) const
{
    const auto& [i, j] = coord;

    return sf::Vector2f(
        offset + (BOARDCELL_SIZE.x * static_cast<float>(j)),
        offset + (BOARDCELL_SIZE.y * static_cast<float>(i))
    );
}

void ButinView::Draw(sf::RenderWindow& window)
{
    window.clear();

    window.draw(m_boardBackgroud);
    DrawBoardCells(window);
    DrawBoardPiece(window);
    window.draw(m_lineSeparator);
    window.draw(m_menuButton);
    if (IsLaunchgameButtonVisible())
        window.draw(m_lauchgameButton);
    window.display();
}

void ButinView::DrawBoardCells(sf::RenderWindow& window)
{
    auto rows = m_boardCell.size();
    auto cols = m_boardCell[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            window.draw(m_boardCell[i][j]);
        }
    }
}

void ButinView::DrawBoardPiece(sf::RenderWindow& window)
{
    auto rows = m_boardPiece.size();
    auto cols = m_boardPiece[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            window.draw(m_boardPiece[i][j]);
        }
    }
}

void ButinView::Render()
{
    UpdateButtonState(m_menuButton, m_flags.m_isMenuButtonSelected, m_flags.m_isMenuButtonHovered, m_flags.m_wasMenuButtonHovered);
    
    if (IsLaunchgameButtonVisible())
        UpdateButtonState(m_lauchgameButton, m_flags.m_isLaunchgameButtonSelected, m_flags.m_isLaunchgameButtonHovered, m_flags.m_wasLaunchgameButtonHovered, m_flags.m_isLaunchgameButtonVisible);
}


std::pair<int, int> ButinView::GetBoardCoord(int x, int y) const 
{
    auto cX = static_cast<int>((x - GameConstants::BOARDOFFSET.x) / BOARDCELL_SIZE.x);
    auto cY = static_cast<int>((y - GameConstants::BOARDOFFSET.y) / BOARDCELL_SIZE.y);

    return std::make_pair(cY, cX);
}

void ButinView::UpdateMenuSelectedFlag(bool newValue)
{
    m_flags.m_isMenuButtonSelected = newValue;
}
void ButinView::UpdateLaunchSelectedFlag(bool newValue)
{
    m_flags.m_isLaunchgameButtonSelected = newValue;
}
void ButinView::UpdateMenuHoveredFlag(bool newValue)
{
    m_flags.m_isMenuButtonHovered = newValue;
}
void ButinView::UpdateLaunchHoveredFlag(bool newValue)
{
    m_flags.m_isLaunchgameButtonHovered = newValue;
}

void ButinView::HideLaunchgameButton()
{
    m_flags.m_isLaunchgameButtonVisible = false;
}

void ButinView::LauchButtonPressed()
{
    m_flags.m_isLaunchgameButtonPressed = true;
}
void ButinView::MenuButtonPressed()
{
    m_flags.m_isMenuButtonPressed = true;
}


sf::Text& ButinView::GetLaunchgameButton()
{
    return m_lauchgameButton;
}
sf::Text& ButinView::GetMenuButton()
{
    return m_menuButton;
}

bool& ButinView::IsLaunchgameButtonSelected() 
{
    return ButinView::m_flags.m_isLaunchgameButtonSelected;
}
bool& ButinView::IsLaunchgameButtonPressed() 
{
    return ButinView::m_flags.m_isLaunchgameButtonPressed;
}
bool& ButinView::IsLaunchgameButtonVisible() 
{
    return ButinView::m_flags.m_isLaunchgameButtonVisible;
}
bool& ButinView::IsMenuButtonSelected() 
{
    return ButinView::m_flags.m_isMenuButtonSelected;
}
bool& ButinView::IsMenuButtonPressed() 
{
    return ButinView::m_flags.m_isMenuButtonPressed;
}

void ButinView::ResetLaunchPressedFlag()
{
    ButinView::m_flags.m_isLaunchgameButtonPressed = false;
}

void ButinView::HighlightCell(std::pair<int, int> coord, sf::Color color)
{
    m_boardCell[coord.first][coord.second].setFillColor(color);
}
void ButinView::RemoveHighlightCell(std::pair<int, int> coord)
{
    if ((coord.first + coord.second) % 2 == 0) m_boardCell[coord.first][coord.second].setFillColor(GameConstants::WHITECELL_COLOR);
    else m_boardCell[coord.first][coord.second].setFillColor(GameConstants::BLACKCELL_COLOR);
}

void ButinView::HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (const auto move : possibleMoves) {
        HighlightCell(move, sf::Color::Green);
    }
}
void ButinView::RemoveHighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (auto move : possibleMoves) {
        RemoveHighlightCell(move);
    }
}

bool& ButinView::HasHighLightedCell()
{
    return m_flags.m_hasHighLightedCell;
}

void ButinView::NeedHighlight()
{
    m_flags.m_hasHighLightedCell = true;
}
void ButinView::RemoveHighlight()
{
    m_flags.m_hasHighLightedCell = false;
}

void ButinView::PrintWinner(const Player* winner) const
{
    system("clear");
    if (winner != nullptr) {
        std::cout << "The winner is: " << winner->ToString() << std::endl;
    } else {
        std::cout << "No winner determined." << std::endl;
    }
}

void ButinView::PrintScore(int score) const{
    std::cout << "Score: " << score << std::endl;
}
