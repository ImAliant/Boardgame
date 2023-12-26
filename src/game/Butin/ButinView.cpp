#include "../../../include/game/Butin/ButinView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace ButinConstants;

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

    InitRectangleShape(m_lineSeparator, UIConstants::LINESEPARATOR_SIZE, UIConstants::LINESEPARATOR_POSITION);

    InitText(m_lauchgameButton, "Lancer la partie", UIConstants::LAUNCHBUTTON_POSITION, *font, UIConstants::CHARACTER_SIZE);
    InitText(m_exitButton, "Quitter", UIConstants::EXITBUTTON_POSITION, *font, UIConstants::CHARACTER_SIZE);




}
void ButinView::PrintCurrentPlayer(std::shared_ptr<Player> currentPlayer) const
{
    std::cout << "Current player: " << currentPlayer->ToString() << std::endl;
}

void ButinView::InitPieceTexture(std::shared_ptr<Context> context)
{
    try 
    {
        LoadTexture(BUTIN_BLACK_PIECE, context);
       
        LoadTexture(BUTIN_RED_PIECE, context);
        LoadTexture(BUTIN_YELLOW_PIECE, context);
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
        BOARDBACKGROUND_SIZE, 
        BOARDBACKGROUND_POSITION
    );
    m_boardBackgroud.setFillColor(BOARDBACKGROUND_COLOR);
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
            InitRectangleShape(
                m_boardCell[i][j],
                BOARDCELL_SIZE,
                CalculatePosition(10.f, i, j)
            );

            if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(WHITECELL_COLOR);
            else m_boardCell[i][j].setFillColor(BLACKCELL_COLOR);
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
            SetupBoardPiece(i, j, board);
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
            SetupBoardPiece(i, j, board);
        }
    }
}



void ButinView::SetupBoardPiece(int i, int j, const ButinBoard &board)
{
    InitRectangleShape(
        m_boardPiece[i][j],
        BOARDPIECE_SIZE,
        CalculatePosition(15.f, i, j)
    );

    auto piece = board.GetValueAt(i, j);
    SetPieceTexture(m_boardPiece[i][j], piece->GetSymbol());
}


void ButinView::SetPieceTexture(sf::RectangleShape &piece, char color)
{  
    if (color == 'Y')
        piece.setTexture(&m_pieceTexture[YELLOW_PAWN_ID]);
    else if (color == 'R')
        piece.setTexture(&m_pieceTexture[RED_PAWN_ID]);
    else if (color == 'B')
        piece.setTexture(&m_pieceTexture[BLACK_PAWN_ID]);
    else 
        piece.setTexture(&m_pieceTexture[EMPTY_ID]);
}




sf::Vector2f ButinView::CalculatePosition(float offset, int i, int j) const
{
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
    window.draw(m_exitButton);
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
    UpdateButtonState(m_exitButton, m_flags.m_isExitButtonSelected, m_flags.m_isExitButtonHovered, m_flags.m_wasExitButtonHovered);
    
    if (IsLaunchgameButtonVisible())
        UpdateButtonState(m_lauchgameButton, m_flags.m_isLaunchgameButtonSelected, m_flags.m_isLaunchgameButtonHovered, m_flags.m_wasLaunchgameButtonHovered, m_flags.m_isLaunchgameButtonVisible);
}


std::pair<int, int> ButinView::GetBoardCoord(int x, int y) const 
{
    auto cX = static_cast<int>((x - BOARDOFFSET.x) / BOARDCELL_SIZE.x);
    auto cY = static_cast<int>((y - BOARDOFFSET.y) / BOARDCELL_SIZE.y);

    return std::make_pair(cY, cX);
}


void ButinView::UpdateExitSelectedFlag(bool newValue)
{
    m_flags.m_isExitButtonSelected = newValue;
}
void ButinView::UpdateLaunchSelectedFlag(bool newValue)
{
    m_flags.m_isLaunchgameButtonSelected = newValue;
}
void ButinView::UpdateExitHoveredFlag(bool newValue)
{
    m_flags.m_isExitButtonHovered = newValue;
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
void ButinView::ExitButtonPressed()
{
    m_flags.m_isExitButtonPressed = true;
}


sf::Text& ButinView::GetLaunchgameButton()
{
    return m_lauchgameButton;
}
sf::Text& ButinView::GetExitButton()
{
    return m_exitButton;
}

std::vector<std::vector<sf::RectangleShape>>& ButinView::GetBoardCell()
{
    return m_boardCell;
}

bool& ButinView::IsLaunchgameButtonSelected() 
{
    return ButinView::m_flags.m_isLaunchgameButtonSelected;
}
bool& ButinView::IsLaunchgameButtonPressed() 
{
    return ButinView::m_flags.m_isLaunchgameButtonPressed;
}
bool& ButinView::IsLaunchgameButtonHovered() 
{
    return ButinView::m_flags.m_isLaunchgameButtonHovered;
}
bool& ButinView::WasLaunchgameButtonHovered() 
{
    return ButinView::m_flags.m_wasLaunchgameButtonHovered;
}
bool& ButinView::IsLaunchgameButtonVisible() 
{
    return ButinView::m_flags.m_isLaunchgameButtonVisible;
}
bool& ButinView::IsExitButtonSelected() 
{
    return ButinView::m_flags.m_isExitButtonSelected;
}
bool& ButinView::IsExitButtonPressed() 
{
    return ButinView::m_flags.m_isExitButtonPressed;
}
bool& ButinView::IsExitButtonHovered() 
{
    return ButinView::m_flags.m_isExitButtonHovered;
}
bool& ButinView::WasExitButtonHovered() 
{
    return ButinView::m_flags.m_wasExitButtonHovered;
}

void ButinView::ResetLaunchPressedFlag()
{
    ButinView::m_flags.m_isLaunchgameButtonPressed = false;
}


//highlight
void ButinView::HighlightCell(std::pair<int, int> coord, sf::Color color)
{
    m_boardCell[coord.first][coord.second].setFillColor(color);
}
void ButinView::RemoveHighlightCell(std::pair<int, int> coord)
{
    if ((coord.first + coord.second) % 2 == 0) m_boardCell[coord.first][coord.second].setFillColor(WHITECELL_COLOR);
    else m_boardCell[coord.first][coord.second].setFillColor(BLACKCELL_COLOR);
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

void ButinView::printWinner(Player* winner) const
{
    if (winner != nullptr) {
        std::cout << "The winner is: " << winner->ToString() << std::endl;
    } else {
        std::cout << "No winner determined." << std::endl;
    }
}
void ButinView::printScore(int score) const{
    std::cout << "Score: " << score << std::endl;
}
