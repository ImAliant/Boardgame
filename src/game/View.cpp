#include "../../include/game/View.hpp"
#include "../../include/exception/AssetNotFoundException.hpp"

using namespace UIConstants;

View::View() {}
View::~View() {}

void View::InitBase(
    std::shared_ptr<Context> context, const Board& board, 
    const std::vector<int>& textureIDs, 
    const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    InitPieceTexture(context, textureIDs);
    InitBoardBackground();
    InitBoardCell(board, cellsize);
    InitBoardPiece(board, piecesize, cellsize);

    sf::Font const* font = &context->m_assets->GetFont(MAIN_FONT);
    if (font == nullptr)
        throw std::runtime_error("View::InitBase() : font is nullptr");

    InitRectangleShape(m_lineSeparator, GameContext::LINESEPARATOR_SIZE, GameContext::LINESEPARATOR_POSITION);

    InitText(m_lauchgameButton, "Lancer la partie", GameContext::LAUNCHBUTTON_POSITION, *font, CHARACTER_SIZE);
    InitText(m_menuButton, "Menu", GameContext::MENUBUTTON_POSITION, *font, CHARACTER_SIZE);
}

void View::InitPieceTexture(const std::shared_ptr<Context> context, const std::vector<int>& textureIDs)
{
    try
    {
        for (const auto& textureID : textureIDs) {
            LoadTexture(textureID, context);
        }
    }
    catch (AssetNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void View::LoadTexture(const int textureID, const std::shared_ptr<Context> context)
{
    if (!context->m_assets->HasTexture(textureID)) {
        throw AssetNotFoundException("Texture not found" + std::to_string(textureID));
    }

    m_pieceTexture.push_back(context->m_assets->GetTexture(textureID));
}

void View::InitBoardBackground()
{
    InitRectangleShape(
        m_boardBackground, 
        GameConstants::BOARDBACKGROUND_SIZE, 
        GameConstants::BOARDBACKGROUND_POSITION
    );
    m_boardBackground.setFillColor(GameConstants::BOARDBACKGROUND_COLOR);
}

void View::InitBoardCell(const Board& board, const sf::Vector2f cellsize)
{
    const auto rows = board.GetRows();
    const auto cols = board.GetCols();

    m_boardCell.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardCell[i].resize(cols);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const auto coord = std::make_pair(i, j);
            InitRectangleShape(
                m_boardCell[i][j],
                cellsize,
                CalculatePosition(10.f, coord, cellsize)
            );

            if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(GameConstants::WHITECELL_COLOR);
            else m_boardCell[i][j].setFillColor(GameConstants::BLACKCELL_COLOR);
        }
    } 
}

void View::InitBoardPiece(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    const auto rows = board.GetRows();
    const auto cols = board.GetCols();

    m_boardPiece.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardPiece[i].resize(cols);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            const auto coord = std::make_pair(i, j);
            SetupBoardPiece(coord, board, piecesize, cellsize);
        }
    }
}

void View::SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    const auto [i, j] = coord;
    InitRectangleShape(
        m_boardPiece[i][j],
        piecesize,
        CalculatePosition(15.f, coord, cellsize)
    );
}

sf::Vector2f View::CalculatePosition(const float offset, const coord_t coord, const sf::Vector2f cellsize) const
{
    const auto& [i, j] = coord;
    return sf::Vector2f(
        offset + (cellsize.x * static_cast<float>(j)),
        offset + (cellsize.y * static_cast<float>(i))
    );
}

void View::Draw(sf::RenderWindow& window)
{
    window.clear();

    window.draw(m_boardBackground);
    DrawBoardCells(window);
    DrawBoardPiece(window);
    window.draw(m_lineSeparator);
    window.draw(m_menuButton);
    if (IsLaunchgameButtonVisible())
        window.draw(m_lauchgameButton);
    window.display();
}
void View::DrawBoardCells(sf::RenderWindow& window)
{
    const auto rows = m_boardCell.size();
    const auto cols = m_boardCell[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols ; j++) {
            window.draw(m_boardCell[i][j]);
        }
    }
}
void View::DrawBoardPiece(sf::RenderWindow& window)
{
    const auto rows = m_boardPiece.size();
    const auto cols = m_boardPiece[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols ; j++) {
            window.draw(m_boardPiece[i][j]);
        }
    }
}

void View::UpdateBoardBase(const Board& board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    const auto rows = board.GetRows();
    const auto cols = board.GetCols();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            const auto coord = std::make_pair(i, j);
            SetupBoardPiece(coord, board, piecesize, cellsize);
        }
    }
}

void View::HighlightCell(const coord_t coord, const sf::Color color)
{
    const auto [i, j] = coord;
    m_boardCell[i][j].setFillColor(color);
}
void View::RemoveHighlightCell(const coord_t coord)
{
    const auto [i, j] = coord;
    if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(GameConstants::WHITECELL_COLOR);
    else m_boardCell[i][j].setFillColor(GameConstants::BLACKCELL_COLOR);
}
void View::HighlightPossibleMoves(const std::vector<coord_t>& possibleMoves)
{
    for (const auto& move: possibleMoves)
        HighlightCell(move, sf::Color::Green);
}
void View::RemoveHighlightPossibleMoves(const std::vector<coord_t>& possibleMoves)
{
    for (const auto& move: possibleMoves)
        RemoveHighlightCell(move);
}

void View::Render()
{
    UpdateButtonState(m_menuButton, m_flags.m_isMenuButtonSelected, m_flags.m_isMenuButtonHovered, m_flags.m_wasMenuButtonHovered);

    if (IsLaunchgameButtonVisible())
        UpdateButtonState(m_lauchgameButton, m_flags.m_isLaunchgameButtonSelected, m_flags.m_isLaunchgameButtonHovered, m_flags.m_wasLaunchgameButtonHovered);
}

void View::UpdateMenuSelectedFlag(const bool newValue)
{
    m_flags.m_isMenuButtonSelected = newValue;
}
void View::UpdateLaunchSelectedFlag(const bool newValue)
{
    m_flags.m_isLaunchgameButtonSelected = newValue;
}
void View::UpdateMenuHoveredFlag(const bool newValue)
{
    m_flags.m_isMenuButtonHovered = newValue;
}
void View::UpdateLaunchHoveredFlag(const bool newValue)
{
    m_flags.m_isLaunchgameButtonHovered = newValue;
}

void View::HideLaunchgameButton()
{
    m_flags.m_isLaunchgameButtonVisible = false;
}
void View::NeedHighlight()
{
    m_flags.m_hasHighLightedCell = true;
}
void View::RemoveHighlight()
{
    m_flags.m_hasHighLightedCell = false;
}
void View::LauchButtonPressed()
{
    m_flags.m_isLaunchgameButtonPressed = true;
}
void View::MenuButtonPressed()
{
    m_flags.m_isMenuButtonPressed = true;
}

void View::ResetLaunchPressedFlag()
{
    m_flags.m_isLaunchgameButtonPressed = false;
}

coord_t View::GetBoardCoordBase(const int x, const int y, const sf::Vector2f cellsize) const
{
    const auto i = static_cast<int>((y - GameConstants::BOARDOFFSET.y) / cellsize.y);
    const auto j = static_cast<int>((x - GameConstants::BOARDOFFSET.x) / cellsize.x);

    return std::make_pair(i, j);
}
sf::Text& View::GetLaunchgameButton()
{
    return m_lauchgameButton;
}
sf::Text& View::GetMenuButton()
{
    return m_menuButton;
}

bool View::IsLaunchgameButtonVisible() const
{
    return m_flags.m_isLaunchgameButtonVisible;
}
bool View::IsLaunchgameButtonSelected() const
{
    return m_flags.m_isLaunchgameButtonSelected;
}
bool View::IsLaunchgameButtonPressed() const
{
    return m_flags.m_isLaunchgameButtonPressed;
}
bool View::IsMenuButtonSelected() const
{
    return m_flags.m_isMenuButtonSelected;
}
bool View::IsMenuButtonPressed() const
{
    return m_flags.m_isMenuButtonPressed;
}
bool View::HasHighLightedCell() const
{
    return m_flags.m_hasHighLightedCell;
}
