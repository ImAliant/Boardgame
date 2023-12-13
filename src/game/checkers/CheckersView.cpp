#include "../../../include/game/checkers/CheckersView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace CheckersConstants;

CheckersView::CheckersView() {}

CheckersView::~CheckersView() {}

void CheckersView::Init(std::shared_ptr<Context> context, const CheckersBoard& board)
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

    InitSizeAndPositionRectangleShape(m_lineSeparator, UIConstants::LINESEPARATOR_SIZE, UIConstants::LINESEPARATOR_POSITION);

    InitText(m_lauchgameButton, "Lancer la partie", UIConstants::LAUNCHBUTTON_POSITION, *font, UIConstants::CHARACTER_SIZE);
    InitText(m_exitButton, "Quitter", UIConstants::EXITBUTTON_POSITION, *font, UIConstants::CHARACTER_SIZE);
}

void CheckersView::InitPieceTexture(std::shared_ptr<Context> context)
{
    try 
    {
        LoadTexture(CHECKERS_BLACK_PIECE, context);
        LoadTexture(CHECKERS_WHITE_PIECE, context);
    }
    catch (AssetNotFoundException& e)
    {
        std::cerr << e.what() << '\n';
    }
}
void CheckersView::LoadTexture(int textureID, std::shared_ptr<Context> context) 
{
    if (!context->m_assets->HasTexture(textureID)) {
        throw AssetNotFoundException("Texture not found" + std::to_string(textureID));
    }

    m_pieceTexture.push_back(context->m_assets->GetTexture(textureID));
}

void CheckersView::InitBoardBackground()
{
    InitSizeAndPositionRectangleShape(
        m_boardBackgroud, 
        BOARDBACKGROUND_SIZE, 
        BOARDBACKGROUND_POSITION
    );
    m_boardBackgroud.setFillColor(BOARDBACKGROUND_COLOR);
}

void CheckersView::InitBoardCell(const CheckersBoard& board)
{
    auto rows = board.GetRows();
    auto cols = board.GetCols();

    m_boardCell.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardCell[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            InitSizeAndPositionRectangleShape(
                m_boardCell[i][j],
                BOARDCELL_SIZE,
                CalculatePosition(10.f, i, j)
            );

            if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(WHITECELL_COLOR);
            else m_boardCell[i][j].setFillColor(BLACKCELL_COLOR);
        }
    }
}

void CheckersView::InitBoardPiece(const CheckersBoard& board)
{
    auto rows = board.GetRows();
    auto cols = board.GetCols();

    m_boardPiece.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardPiece[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            InitSizeAndPositionRectangleShape(
                m_boardPiece[i][j],
                BOARDPIECE_SIZE,
                CalculatePosition(15.f, i, j)
            );

            auto color = board.GetValueAt(i, j)->GetColor();
            if (color == sf::Color::Black)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[BLACKPIECE_TEXTUREID]);
            else if (color == sf::Color::White) 
                m_boardPiece[i][j].setTexture(&m_pieceTexture[WHITEPIECE_TEXTUREID]);
            else m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
        }
    }
}
sf::Vector2f CheckersView::CalculatePosition(float offset, int i, int j) const
{
    return sf::Vector2f(
        offset + (BOARDCELL_SIZE.x * static_cast<float>(j)),
        offset + (BOARDCELL_SIZE.y * static_cast<float>(i))
    );
}

void CheckersView::Draw(sf::RenderWindow& window)
{
    window.clear();
    window.draw(m_boardBackgroud);
    DrawBoardCells(window);
    DrawBoardPiece(window);
    window.draw(m_lineSeparator);
    window.draw(m_exitButton);
    window.draw(m_lauchgameButton);
    window.display();
}

void CheckersView::DrawBoardCells(sf::RenderWindow& window)
{
    auto rows = m_boardCell.size();
    auto cols = m_boardCell[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            window.draw(m_boardCell[i][j]);
        }
    }
}

void CheckersView::DrawBoardPiece(sf::RenderWindow& window)
{
    auto rows = m_boardPiece.size();
    auto cols = m_boardPiece[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            window.draw(m_boardPiece[i][j]);
        }
    }
}

void CheckersView::HighlightCell(std::pair<int, int> coord, sf::Color color)
{
    m_boardCell[coord.first][coord.second].setFillColor(color);
}
void CheckersView::RemoveHighlightCell(std::pair<int, int> coord)
{
    if ((coord.first + coord.second) % 2 == 0) m_boardCell[coord.first][coord.second].setFillColor(WHITECELL_COLOR);
    else m_boardCell[coord.first][coord.second].setFillColor(BLACKCELL_COLOR);
}

void CheckersView::HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (const auto move : possibleMoves) {
        HighlightCell(move, sf::Color::Green);
    }
}
void CheckersView::RemoveHighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (auto move : possibleMoves) {
        RemoveHighlightCell(move);
    }
}

void CheckersView::HideLaunchgameButton()
{
    m_flags.m_isLaunchgameButtonVisible = false;
}

void CheckersView::RenderButton()
{
    UpdateButtonState(m_exitButton, m_flags.m_isExitButtonSelected, m_flags.m_isExitButtonHovered, m_flags.m_wasExitButtonHovered);
    UpdateButtonState(m_lauchgameButton, m_flags.m_isLaunchgameButtonSelected, m_flags.m_isLaunchgameButtonHovered, m_flags.m_wasLaunchgameButtonHovered, m_flags.m_isLaunchgameButtonVisible);
}

std::pair<int, int> CheckersView::GetBoardCoord(int x, int y) const 
{
    auto cX = static_cast<int>((x - BOARDOFFSET.x) / BOARDCELL_SIZE.x);
    auto cY = static_cast<int>((y - BOARDOFFSET.y) / BOARDCELL_SIZE.y);

    return std::make_pair(cY, cX);
}

void CheckersView::UpdateFlag(bool& flagToUpdate, bool newValue) const
{
    if (flagToUpdate != newValue) {
        flagToUpdate = newValue;
    }
}

sf::Text& CheckersView::GetLaunchgameButton()
{
    return m_lauchgameButton;
}
sf::Text& CheckersView::GetExitButton()
{
    return m_exitButton;
}
std::vector<std::vector<sf::RectangleShape>>& CheckersView::GetBoardCell()
{
    return m_boardCell;
}

bool& CheckersView::GetBoardNeedUpdate() 
{
    return m_flags.m_boardNeedUpdate;
}
bool& CheckersView::GetIsLaunchgameButtonSelected() 
{
    return m_flags.m_isLaunchgameButtonSelected;
}
bool& CheckersView::GetIsLaunchgameButtonPressed() 
{
    return m_flags.m_isLaunchgameButtonPressed;
}
bool& CheckersView::GetIsLaunchgameButtonHovered() 
{
    return m_flags.m_isLaunchgameButtonHovered;
}
bool& CheckersView::GetWasLaunchgameButtonHovered() 
{
    return m_flags.m_wasLaunchgameButtonHovered;
}
bool& CheckersView::GetIsLaunchgameButtonVisible() 
{
    return m_flags.m_isLaunchgameButtonVisible;
}
bool& CheckersView::GetIsExitButtonSelected() 
{
    return m_flags.m_isExitButtonSelected;
}
bool& CheckersView::GetIsExitButtonPressed() 
{
    return m_flags.m_isExitButtonPressed;
}
bool& CheckersView::GetIsExitButtonHovered() 
{
    return m_flags.m_isExitButtonHovered;
}
bool& CheckersView::GetWasExitButtonHovered() 
{
    return m_flags.m_wasExitButtonHovered;
}
bool& CheckersView::GetHasHighLightedCell()
{
    return m_flags.m_hasHighLightedCell;
}