#include "../../../include/game/checkers/CheckersView.hpp"

CheckersView::CheckersView() {}

CheckersView::~CheckersView() {}

void CheckersView::Init(std::shared_ptr<Context> context, const Board& board)
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

    InitSizeAndPositionRectangleShape(m_lineSeparator1, sf::Vector2f(static_cast<float>(WINDOW_SIZE.x), 2), sf::Vector2f(0.f, static_cast<float>(WINDOW_SIZE.y) - 100.f));

    InitText(m_lauchgameButton, "Lancer la partie", sf::Vector2f(static_cast<float>(WINDOW_SIZE.x) / 2, static_cast<float>(WINDOW_SIZE.y) - 80.f), *font, 20);
    InitText(m_exitButton, "Quitter", sf::Vector2f(static_cast<float>(WINDOW_SIZE.x) / 2, static_cast<float>(WINDOW_SIZE.y) - 30.f), *font, 20);
}

void CheckersView::InitPieceTexture(std::shared_ptr<Context> context)
{
    if (!context->m_assets->HasTexture(CHECKERS_BLACK_PIECE)) {
        std::cout << "Texture not found: CHECKERS_BLACK_PIECE" << std::endl;
        // TODO: use a dedicated exception
        throw std::runtime_error("Texture not found");
    }
    if (!context->m_assets->HasTexture(CHECKERS_WHITE_PIECE)) {
        std::cout << "Texture not found: CHECKERS_WHITE_PIECE" << std::endl;
        // TODO : use a dedicated exception
        throw std::runtime_error("Texture not found");
    }
    else {
        m_pieceTexture.push_back(context->m_assets->GetTexture(CHECKERS_BLACK_PIECE));
        m_pieceTexture.push_back(context->m_assets->GetTexture(CHECKERS_WHITE_PIECE));
    }
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

void CheckersView::InitBoardCell(const Board& board)
{
    auto rows = board.getRows();
    auto cols = board.getCols();

    m_boardCell.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardCell[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            InitSizeAndPositionRectangleShape(
                m_boardCell[i][j],
                BOARDCELL_SIZE,
                sf::Vector2f(
                    10.f + (BOARDCELL_SIZE.x * static_cast<float>(j)),
                    10.f + (BOARDCELL_SIZE.y * static_cast<float>(i))
                )
            );

            if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(WHITECELL_COLOR);
            else m_boardCell[i][j].setFillColor(BLACKCELL_COLOR);
        }
    }
}

void CheckersView::InitBoardPiece(const Board& board)
{
    auto rows = board.getRows();
    auto cols = board.getCols();

    m_boardPiece.resize(rows);
    for (int i = 0; i < rows; i++) {
        m_boardPiece[i].resize(cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols ; j++) {
            InitSizeAndPositionRectangleShape(
                m_boardPiece[i][j],
                BOARDPIECE_SIZE,
                sf::Vector2f(
                    15.f + (BOARDCELL_SIZE.x * static_cast<float>(j)),
                    15.f + (BOARDCELL_SIZE.y * static_cast<float>(i))
                )
            );

            auto color = board.getValueAt(i, j)->getColor();
            if (color == sf::Color::Black)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[0]); // ID TEXTURE NOIRE
            else if (color == sf::Color::White) 
                m_boardPiece[i][j].setTexture(&m_pieceTexture[1]); // ID TEXTURE BLANCHE
            else m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
        }
    }
}

void CheckersView::Draw(sf::RenderWindow& window)
{
    window.clear();
    window.draw(m_boardBackgroud);
    DrawBoardCells(window);
    DrawBoardPiece(window);
    window.draw(m_lineSeparator1);
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
    m_isLaunchgameButtonVisible = false;
}

void CheckersView::RenderButton()
{
    UpdateButtonState(m_exitButton, m_isExitButtonSelected, m_isExitButtonHovered, m_wasExitButtonHovered);
    UpdateButtonState(m_lauchgameButton, m_isLaunchgameButtonSelected, m_isLaunchgameButtonHovered, m_wasLaunchgameButtonHovered, m_isLaunchgameButtonVisible);
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
    return m_boardNeedUpdate;
}
bool& CheckersView::GetIsLaunchgameButtonSelected() 
{
    return m_isLaunchgameButtonSelected;
}
bool& CheckersView::GetIsLaunchgameButtonPressed() 
{
    return m_isLaunchgameButtonPressed;
}
bool& CheckersView::GetIsLaunchgameButtonHovered() 
{
    return m_isLaunchgameButtonHovered;
}
bool& CheckersView::GetWasLaunchgameButtonHovered() 
{
    return m_wasLaunchgameButtonHovered;
}
bool& CheckersView::GetIsLaunchgameButtonVisible() 
{
    return m_isLaunchgameButtonVisible;
}
bool& CheckersView::GetIsExitButtonSelected() 
{
    return m_isExitButtonSelected;
}
bool& CheckersView::GetIsExitButtonPressed() 
{
    return m_isExitButtonPressed;
}
bool& CheckersView::GetIsExitButtonHovered() 
{
    return m_isExitButtonHovered;
}
bool& CheckersView::GetWasExitButtonHovered() 
{
    return m_wasExitButtonHovered;
}
bool& CheckersView::GetHasHighLightedCell()
{
    return m_hasHighLightedCell;
}