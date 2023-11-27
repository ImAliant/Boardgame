#include "../../include/game/Checkers.hpp"

#include <random>

Checkers::Checkers(const std::shared_ptr<Context> &context): m_context(context) {}

Checkers::~Checkers() {}

void Checkers::Init() 
{
    m_context->m_window->setTitle("Les Dames - Diamant/Hamdi");

    auto width = static_cast<float>(m_context->m_window->getSize().x);
    auto height = static_cast<float>(m_context->m_window->getSize().y);
    auto backgroundBoardWidth = width - 10.f; // 490 px
    auto backgroundBoardHeight = height - 110.f; // 490 px
    auto cellWidth = (backgroundBoardWidth - 10.f) / BOARD_SIZE;
    auto cellHeight = (backgroundBoardHeight - 10.f) / BOARD_SIZE;
    auto pieceWidth = cellWidth - 10.f;
    auto pieceHeight = cellHeight - 10.f;

    // players
    initPlayers();
    m_board = std::make_unique<Board>(GameType::CHECKERS, m_players);
    if (m_board.get()->getRows() != BOARD_SIZE || m_board.get()->getCols() != BOARD_SIZE)
    {
        std::cout << "The size of the board is invalid\n";
        return;
    }

    // textures
    initPieceTexture();

    // background board
    initBoardBackground(backgroundBoardWidth, backgroundBoardHeight);
    
    // board: cells
    initBoardCells(cellWidth, cellHeight);

    // board: pieces
    initBoardPieces(pieceWidth, pieceHeight, cellWidth, cellHeight);

    // line separators
    InitSizeAndPositionRectangleShape(m_lineSeparator1, sf::Vector2f(width, 2), sf::Vector2f(0.f, height - 100.f));
    InitSizeAndPositionRectangleShape(m_lineSeparator2, sf::Vector2f(width, 2), sf::Vector2f(0.f, height - 50.f));

    // launch game button
    InitText(m_lauchgameButton, "Lancer la partie", sf::Vector2f(width / 2, height - 80.f), 20);
    // exit button
    InitText(m_exitButton, "Quitter", sf::Vector2f(width / 2, height - 30.f), 20);
}

void Checkers::ProcessInput() 
{
    sf::Event event;

    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            closeWindow();
        }

        UpdateButtonHoverState(event);

        if (event.type == sf::Event::MouseMoved)
        {
            UpdateButtonSelectionState();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            HandleMousePressed(event);
        }
    }
}

void Checkers::Update() 
{
    UpdateButtonState(m_exitButton, m_isExitButtonSelected, m_isExitButtonHovered, m_wasExitButtonHovered);
    UpdateButtonState(m_lauchgameButton, m_isLaunchgameButtonSelected, m_isLaunchgameButtonHovered, m_wasLaunchgameButtonHovered, m_isLaunchgameButtonVisible);

    if (m_isLaunchgameButtonPressed)
    {
        m_isLaunchgameButtonPressed = false;
        m_isGameStarted = true;
        m_isLaunchgameButtonVisible = false;

        // random player to start
        /*std::mt19937 rng(std::random_device{}());
        int randomPlayer = rng() % 2;*/

        //m_currentPlayer = m_players[randomPlayer];
        m_currentPlayer = m_players[0];

        updatePossibleMoves();
    }

    if (m_boardNeedUpdate)
    {
        UpdateBoard();
        m_boardNeedUpdate = false;
    }

    if (m_isExitButtonPressed) {
        m_context->m_states->PopAll();
        m_context->m_window->close();
    }
}

void Checkers::DrawBoardCells()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            m_context->m_window->draw(m_boardCell[i][j]);
        }
    }
}

void Checkers::DrawBoardPieces()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            m_context->m_window->draw(m_boardPiece[i][j]);
        }
    }
}

void Checkers::Draw() 
{
    m_context->m_window->clear();
    // draw of the background board
    m_context->m_window->draw(m_boardBackgroud);
    // draw of the board cells
    DrawBoardCells();
    // draw of the board pieces
    DrawBoardPieces();
    // draw of the line separators
    m_context->m_window->draw(m_lineSeparator1);
    m_context->m_window->draw(m_lineSeparator2);
    // draw of the buttons
    m_context->m_window->draw(m_lauchgameButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

void Checkers::Start() 
{
    while (m_context->m_window->isOpen())
    {
        ProcessInput();
        Update();
        Draw();
    }
}

void Checkers::doPlayerTurn(const sf::Event::MouseButtonEvent &event)
{
    std::cout << "doPlayerTurn()\n";

    // if the click is on the board (not on the buttons)
    // so if the click is between 10,10 and 480, 480 the player can play
    if (event.x < 10 || event.x > 480 || event.y < 10 || event.y > 480) return;

    sf::Vector2f boardPos = m_context->m_window->mapPixelToCoords(sf::Vector2i(event.x, event.y));
    auto x = static_cast<int>(boardPos.x / 50.f);
    auto y = static_cast<int>(boardPos.y / 50.f);

    std::cout << "x: " << y << " y: " << x << std::endl;

    // select or deselect a piece
    if (m_selectedPiece.first == -1 && m_selectedPiece.second == -1) 
        selectPiece(boardPos, x, y);
    else deselectPiece(x, y);

    // move the piece
    if (m_selectedPiece.first != -1 && m_selectedPiece.second != -1 && m_isPieceSelected) 
    {
        std::cout << "debug" << std::endl;
        if (m_board.get()->getValueAt(m_selectedPiece.first, m_selectedPiece.second)->getPossibleMoves().empty()) return;
        movePiece(event);
    }
}

void Checkers::movePiece(const sf::Event::MouseButtonEvent &event) 
{
    std::cout << "movePiece() << x: " << m_selectedPiece.first << " y: " << m_selectedPiece.second << std::endl;
    // select the cell where the piece will be moved
    //if (m_boardCell[y][x].getGlobalBounds().contains(boardPos))
    //{
    //    // on test si la case où on veut déplacer la pièce est une case où la pièce peut se déplacer
    //    std::vector<std::pair<int, int>> possibleMoves = m_board.get()->getValueAt(m_selectedPiece.first, m_selectedPiece.second)->getPossibleMoves();
    //    for (auto const &move : possibleMoves)
    //    {
    //        if (move.first == x && move.second == y)
    //        {
    //            m_board.get()->movePiece(m_selectedPiece.first, m_selectedPiece.second, y, x);
    //            m_boardNeedUpdate = true;

                // on enlève la couleur verte des cases où la pièce pouvait se déplacer
    //            for (auto const &move : possibleMoves)
    //            {
    //                if ((move.first + move.second) % 2 == 0) m_boardCell[move.second][move.first].setFillColor(WHITECELL_COLOR);
    //                else m_boardCell[move.second][move.first].setFillColor(BLACKCELL_COLOR);
    //            }

    //            m_selectedPiece = std::make_pair(-1, -1);
    //            m_isPieceSelected = false;
    //        }
    //    }
    //}
}

void Checkers::selectPiece(sf::Vector2f boardPos, int x, int y)
{
    if (m_boardPiece[y][x].getGlobalBounds().contains(boardPos))
    {
        if (m_board.get()->getValueAt(y, x)->getOwner().getId() == m_currentPlayer.get()->getId())
        {
            m_selectedPiece = std::make_pair(y, x);
            
            std::vector<std::pair<int, int>> possibleMoves = m_board.get()->getValueAt(m_selectedPiece.first, m_selectedPiece.second)->getPossibleMoves();
            for (const auto &move : possibleMoves)
            {
                m_boardCell[move.second][move.first].setFillColor(sf::Color::Green);
            }

            m_isPieceSelected = true;
        }
    }
}

void Checkers::deselectPiece(int x, int y) 
{
    if (m_selectedPiece.first == y && m_selectedPiece.second == x)
    {
        std::vector<std::pair<int, int>> possibleMoves = m_board.get()->getValueAt(m_selectedPiece.first, m_selectedPiece.second)->getPossibleMoves();
        for (auto const &move : possibleMoves)
        {
            if ((move.first + move.second) % 2 == 0) m_boardCell[move.second][move.first].setFillColor(WHITECELL_COLOR);
            else m_boardCell[move.second][move.first].setFillColor(BLACKCELL_COLOR);
        }

        m_selectedPiece = std::make_pair(-1, -1);
        m_isPieceSelected = false;
    }
}

void Checkers::promotePiece(const sf::Vector2i &position) 
{

}

void Checkers::checkForWin() 
{

}

void Checkers::switchPlayer() 
{
    
}

void Checkers::UpdateBoard()
{
    // update the board pieces
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            if (m_board.get()->getValueAt(i, j)->getColor() == sf::Color::Black)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[BLACKPIECE_TEXTUREID]);
            else if (m_board.get()->getValueAt(i, j)->getColor() == sf::Color::White)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[WHITEPIECE_TEXTUREID]);
            else
                m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
        }
    }
}

void Checkers::updatePossibleMoves() const
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            m_board.get()->getValueAt(i, j)->findPossibleMoves(*m_board.get());
        }
    }
}

void Checkers::initPlayers()
{
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_ONE));
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_TWO));
    m_players.push_back(std::make_shared<Player>(Players::NONE));
}

void Checkers::initPieceTexture()
{
    if (!m_context->m_assets->HasTexture(CHECKERS_BLACK_PIECE))
        m_context->m_assets->AddTexture(CHECKERS_BLACK_PIECE, "../../assets/images/checkers/black_piece.png");
    else if (!m_context->m_assets->HasTexture(CHECKERS_WHITE_PIECE))
        m_context->m_assets->AddTexture(CHECKERS_WHITE_PIECE, "../../assets/images/checkers/white_piece.png");
    else 
    {
        m_pieceTexture[BLACKPIECE_TEXTUREID] = m_context->m_assets->GetTexture(CHECKERS_BLACK_PIECE);
        m_pieceTexture[WHITEPIECE_TEXTUREID] = m_context->m_assets->GetTexture(CHECKERS_WHITE_PIECE);
    }
}

void Checkers::initBoardBackground(float backgroundBoardWidth, float backgroundBoardHeight)
{
    InitSizeAndPositionRectangleShape(m_boardBackgroud,
                                      sf::Vector2f(backgroundBoardWidth, backgroundBoardHeight),
                                      sf::Vector2f(5.f, 5.f)
                                    );
    m_boardBackgroud.setFillColor(BACKGROUND_COLOR);
}

void Checkers::initBoardCells(float cellWidth, float cellHeight) 
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            InitSizeAndPositionRectangleShape(m_boardCell[i][j], 
                                              sf::Vector2f(cellWidth, cellHeight), 
                                              sf::Vector2f(10.f + (cellWidth * static_cast<float>(i)), 10.f + (cellHeight * static_cast<float>(j)))
                                            );

            if ((i + j) % 2 == 0) m_boardCell[i][j].setFillColor(WHITECELL_COLOR);
            else m_boardCell[i][j].setFillColor(BLACKCELL_COLOR);
        }
    }
}

void Checkers::initBoardPieces(float pieceWidth, float pieceHeight, float cellWidth, float cellHeight)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {         
            InitSizeAndPositionRectangleShape(m_boardPiece[i][j],
                                              sf::Vector2f(pieceWidth, pieceHeight),
                                              sf::Vector2f(15.f + (cellWidth * static_cast<float>(j)), 15.f + (cellHeight * static_cast<float>(i)))
                                            );
            
            if (m_board.get()->getValueAt(i, j)->getColor() == sf::Color::Black)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[BLACKPIECE_TEXTUREID]);
            else if (m_board.get()->getValueAt(i, j)->getColor() == sf::Color::White)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[WHITEPIECE_TEXTUREID]);
            else
                m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
        }
    }
}

void Checkers::InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize)
{
    sf::Font const* font = &m_context->m_assets->GetFont(MAIN_FONT); 
    if (font == nullptr)
    {
        std::cout << "The font of is not loaded" << std::endl;
        return;
    }

    object.setFont(*font);
    object.setString(text);
    object.setCharacterSize(characterSize);
    object.setOrigin(object.getGlobalBounds().width / 2, object.getGlobalBounds().height / 2);
    object.setPosition(position);
}

void Checkers::closeWindow() const
{
    m_context->m_states->PopAll();
    m_context->m_window->close();
}

void Checkers::UpdateButtonHoverState(const sf::Event& event) 
{
    m_isExitButtonHovered = m_exitButton.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
    m_isLaunchgameButtonHovered = m_lauchgameButton.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
}

void Checkers::UpdateButtonSelectionState() 
{
    m_isExitButtonSelected = m_isExitButtonHovered;
    m_isLaunchgameButtonSelected = m_isLaunchgameButtonHovered;
}

void Checkers::HandleMousePressed(const sf::Event& event)
{
    bool isMouseLeftButtonPressed = event.mouseButton.button == sf::Mouse::Left;
    if (isMouseLeftButtonPressed)
    {
        if (m_isExitButtonSelected) m_isExitButtonPressed = true;
        if (m_isLaunchgameButtonSelected) m_isLaunchgameButtonPressed = true;
        if (m_isGameStarted) doPlayerTurn(event.mouseButton);
    }
}