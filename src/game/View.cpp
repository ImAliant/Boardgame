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

    std::array<std::function<void()>, GameContext::NUMBER_OF_BUTTONS> functions =
    {
        [this]() { LauchButtonPressed(); },
        [this]() { MenuButtonPressed(); }
    };

    for (int i = 0; i < GameContext::NUMBER_OF_TEXTS; i++)
    {
        m_texts.emplace_back();
    }

    InitButton(GameContext::LAUNCHBUTTONID, "Lancer la partie", GameContext::LAUNCHBUTTON_POSITION, *font, functions[GameContext::LAUNCHBUTTONID]);
    InitButton(GameContext::MENUBUTTONID, "Menu", GameContext::MENUBUTTON_POSITION, *font, functions[GameContext::MENUBUTTONID]);
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

    for (const auto& button : m_buttons)
    {
        if (button->m_isVisible)
            window.draw(button->m_button);
    }

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
    for (const auto& button : m_buttons)
    {
        if (button->m_isVisible)
            UpdateButtonState(button->m_button, button->m_isSelected, button->m_isHovered, button->m_wasHovered);
    }
}

void View::UpdateMenuSelectedFlag(const bool newValue)
{
    m_buttons[1]->m_isSelected = newValue;
}
void View::UpdateLaunchSelectedFlag(const bool newValue)
{
    m_buttons[0]->m_isSelected = newValue;
}
void View::UpdateMenuHoveredFlag(const bool newValue)
{
    m_buttons[1]->m_isHovered = newValue;
}
void View::UpdateLaunchHoveredFlag(const bool newValue)
{
    m_buttons[0]->m_isHovered = newValue;
}

void View::HideLaunchgameButton()
{
    m_buttons[0]->m_isVisible = false;
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
    m_buttons[0]->m_isPressed = true;
}
void View::MenuButtonPressed()
{
    m_buttons[1]->m_isPressed = true;
}

void View::ResetLaunchPressedFlag()
{
    m_buttons[0]->m_isPressed = false;
}

coord_t View::GetBoardCoordBase(const int x, const int y, const sf::Vector2f cellsize) const
{
    const auto i = static_cast<int>((y - GameConstants::BOARDOFFSET.y) / cellsize.y);
    const auto j = static_cast<int>((x - GameConstants::BOARDOFFSET.x) / cellsize.x);

    return std::make_pair(i, j);
}
sf::Text& View::GetLaunchgameButton()
{
    return m_buttons[0]->m_button;
}
sf::Text& View::GetMenuButton()
{
    return m_buttons[1]->m_button;
}

bool View::IsLaunchgameButtonVisible() const
{
    return m_buttons[0]->m_isVisible;
}
bool View::IsLaunchgameButtonSelected() const
{
    return m_buttons[0]->m_isSelected;
}
bool View::IsLaunchgameButtonPressed() const
{
    return m_buttons[0]->m_isPressed;
}
bool View::IsMenuButtonSelected() const
{
    return m_buttons[1]->m_isSelected;
}
bool View::IsMenuButtonPressed() const
{
    return m_buttons[1]->m_isPressed;
}
bool View::HasHighLightedCell() const
{
    return m_flags.m_hasHighLightedCell;
}
