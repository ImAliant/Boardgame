
#include "../../include/game/Butin.hpp"
#include <iostream>

using namespace butin;
Butin::Butin(const std::shared_ptr<Context> &context): m_context(context),selectedPieceX(-1), selectedPieceY(-1),m_currentPlayerIndex(0) {}

Butin::~Butin() {}  




void Butin::Init()
{
    auto width = static_cast<float>(m_context->m_window->getSize().x);
    auto height = static_cast<float>(m_context->m_window->getSize().y);
    auto backgroundBoardWidth = width - 10.f; // 490 px
    auto backgroundBoardHeight = height - 110.f; // 490 px
    auto cellWidth = (backgroundBoardWidth - 10.f) / BOARD_SIZE;
    auto cellHeight = (backgroundBoardHeight - 10.f) / BOARD_SIZE;
    auto pieceWidth = cellWidth - 10.f;
    auto pieceHeight = cellHeight - 10.f;

    initPlayers();
    m_board = std::make_unique<Board>(GameType::BUTIN, m_players);
    if (m_board.get()->getRows() != BOARD_SIZE || m_board.get()->getCols() != BOARD_SIZE)
        {
            std::cout << "The size of the board is invalid\n";
            return;
        }

        initPieceTexture();
        initBoardBackground(backgroundBoardWidth, backgroundBoardHeight);
        initBoardCells(cellWidth, cellHeight);
        initBoardPieces(pieceWidth, pieceHeight,cellWidth, cellHeight);
// line separators
    InitSizeAndPositionRectangleShape(m_lineSeparator1, sf::Vector2f(width, 2), sf::Vector2f(0.f, height - 100.f));
    InitSizeAndPositionRectangleShape(m_lineSeparator2, sf::Vector2f(width, 2), sf::Vector2f(0.f, height - 50.f));

    // launch game button
    InitText(m_lauchgameButton, "Lancer la partie", sf::Vector2f(width / 2, height - 80.f), 20);
    // exit button
    InitText(m_exitButton, "Quitter", sf::Vector2f(width / 2, height - 30.f), 20);
    printBoardState();
}


void Butin::ProcessInput() 
{

auto width = static_cast<float>(m_context->m_window->getSize().x);
    auto height = static_cast<float>(m_context->m_window->getSize().y);
    auto backgroundBoardWidth = width - 10.f; // 490 px
    auto backgroundBoardHeight = height - 110.f; // 490 px
    auto cellWidth = (backgroundBoardWidth - 10.f) / BOARD_SIZE;
    auto cellHeight = (backgroundBoardHeight - 10.f) / BOARD_SIZE;
    auto pieceWidth = cellWidth - 10.f;
    auto pieceHeight = cellHeight - 10.f;


    sf::Event event;

    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            closeWindow();
        }
    if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                // Space key pressed, end current player's turn
                if (m_isGameStarted) {
                    nextPlayerTurn();
                }
            }
        }


      if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed) {
     /*       // Convert mouse position to board coordinates
            sf::Vector2f boardPos = m_context->m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_context->m_window));
            const float boardOriginX = 5.f;  // Margin from the left
            const float boardOriginY = 5.f;  // Margin from the top

            int boardX = static_cast<int>((boardPos.x - boardOriginX) / cellWidth);
            int boardY = static_cast<int>((boardPos.y - boardOriginY) / cellHeight);

            // Ensure board coordinates are within bounds
            if (boardX >= 0 && boardX < BOARD_SIZE && boardY >= 0 && boardY < BOARD_SIZE) {
                std::cout << "Mouse Board Coordinates: x=" << boardX << ", y=" << boardY << std::endl;
                // Additional logic for mouse clicks
            }*/


        UpdateButtonHoverState(event);
        }
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


void Butin::Update()
{
    UpdateButtonState(m_exitButton, m_isExitButtonSelected, m_isExitButtonHovered, m_wasExitButtonHovered);
    UpdateButtonState(m_lauchgameButton, m_isLaunchgameButtonSelected, m_isLaunchgameButtonHovered, m_wasLaunchgameButtonHovered, m_isLaunchgameButtonVisible);

    if (m_isLaunchgameButtonPressed)
    {
        m_isLaunchgameButtonPressed = false;
        m_isGameStarted = true;
        m_isLaunchgameButtonVisible = false;

        // Select the initial player
        //std::mt19937 rng(std::random_device{}());
        //int randomPlayer = rng() % m_players.size();
        m_currentPlayer = m_players[0];
        m_currentRound = 1;

        m_boardNeedUpdate = true;
    }

   if (m_boardNeedUpdate)
    {
        UpdateBoard();
        m_boardNeedUpdate = false;
    }

    if (m_isExitButtonPressed)
    {
        closeWindow();
    }
}

void Butin::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_boardBackgroud);
    DrawBoardCells();
    DrawBoardPieces();
    m_context->m_window->draw(m_lineSeparator1);
    m_context->m_window->draw(m_lineSeparator2);
    m_context->m_window->draw(m_lauchgameButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

void Butin::initPieceTexture()
{
    // Load Yellow Piece Texture
    if (!m_context->m_assets->HasTexture(BUTIN_YELLOW_PIECE))
        m_context->m_assets->AddTexture(BUTIN_YELLOW_PIECE, "/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/assets/images/Butin/yellow_pice.png");
    
    // Load Red Piece Texture
    if (!m_context->m_assets->HasTexture(BUTIN_RED_PIECE))
        m_context->m_assets->AddTexture(BUTIN_RED_PIECE, "/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/assets/images/Butin/red_piece.png");

    // Load Black Piece Texture
    if (!m_context->m_assets->HasTexture(BUTIN_BLACK_PIECE))
        m_context->m_assets->AddTexture(BUTIN_BLACK_PIECE, "/home/yahya/Desktop/M1/S1/langObj/projet/diamant-hamdi-cpp-boardgames/assets/images/Butin/black_piece.png");
    
    // Assigning textures to the texture map/array
    m_pieceTexture[YELLOWPIECE_TEXTUREID] = m_context->m_assets->GetTexture(BUTIN_YELLOW_PIECE);
    m_pieceTexture[REDPIECE_TEXTUREID] = m_context->m_assets->GetTexture(BUTIN_RED_PIECE);
    m_pieceTexture[BLACKPIECE_TEXTUREID] = m_context->m_assets->GetTexture(BUTIN_BLACK_PIECE);
}








void Butin::initPlayers()
{
    // Adjust the number of players according to your minimum requirement
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_ONE));
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_TWO));
}

void Butin::initBoardBackground(float backgroundBoardWidth, float backgroundBoardHeight)
{
    // Initialize the background board
    InitSizeAndPositionRectangleShape(m_boardBackgroud,
                                      sf::Vector2f(backgroundBoardWidth, backgroundBoardHeight),
                                      sf::Vector2f(5.f, 5.f));
    m_boardBackgroud.setFillColor(BACKGROUND_COLOR);
}

void Butin::initBoardCells(float cellWidth, float cellHeight)
{
    // Initialize the cells of the board
    for (int i = 0; i < butin::BOARD_SIZE; i++)
    {
        for (int j = 0; j < butin::BOARD_SIZE; j++)
        {
            InitSizeAndPositionRectangleShape(m_boardCell[i][j],
                                              sf::Vector2f(cellWidth, cellHeight),
                                              sf::Vector2f(10.f + (cellWidth * static_cast<float>(i)), 10.f + (cellHeight * static_cast<float>(j))));

            if ((i + j) % 2 == 0)
                m_boardCell[i][j].setFillColor(WHITECELL_COLOR);
            else
                m_boardCell[i][j].setFillColor(BLACKCELL_COLOR);
        }
    }
}

void Butin::initBoardPieces(float pieceWidth, float pieceHeight, float cellWidth, float cellHeight)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            InitSizeAndPositionRectangleShape(m_boardPiece[i][j],
                                              sf::Vector2f(pieceWidth, pieceHeight),
                                              sf::Vector2f(15.f + (cellWidth * static_cast<float>(j)), 15.f + (cellHeight * static_cast<float>(i)))
                                             );
            
            sf::Color pieceColor = m_board.get()->getValueAt(i, j)->getColor();
            if (pieceColor == sf::Color::Yellow){
            std::cout << "db Yellow"  << std::endl;
                m_boardPiece[i][j].setTexture(&m_pieceTexture[YELLOWPIECE_TEXTUREID]);
            }else if (pieceColor == sf::Color::Red)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[REDPIECE_TEXTUREID]);
            else if (pieceColor == sf::Color::Black)
                m_boardPiece[i][j].setTexture(&m_pieceTexture[BLACKPIECE_TEXTUREID]);
            else
                m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
        }
    }
}
void Butin::DrawBoardPieces()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) 
        {
            m_context->m_window->draw(m_boardPiece[i][j]);
        }
    }
}

void Butin::DrawBoardCells()
{
    // Draw the cells of the board
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            m_context->m_window->draw(m_boardCell[i][j]);
        }
    }
}

void Butin::InitText(sf::Text &object, const std::string &text, const sf::Vector2f &position, const int &characterSize)
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

void Butin::UpdateBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece* piece = m_board.get()->getValueAt(i, j);

            if (piece) {
                // Set the texture based on the piece's color
                if (piece->getColor() == sf::Color::Yellow) {
                    m_boardPiece[i][j].setTexture(&m_pieceTexture[YELLOWPIECE_TEXTUREID]);
                } else if (piece->getColor() == sf::Color::Red) {
                    m_boardPiece[i][j].setTexture(&m_pieceTexture[REDPIECE_TEXTUREID]);
                } else if (piece->getColor() == sf::Color::Black) {
                    m_boardPiece[i][j].setTexture(&m_pieceTexture[BLACKPIECE_TEXTUREID]);
                } else {
                    // If there's no piece, make the cell transparent
                    m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
                }
            } else {
                // If there's no piece, make the cell transparent
                m_boardPiece[i][j].setFillColor(sf::Color::Transparent);
            }
        }
    }

    // Refresh the window or the specific area that represents the board
    // ... (this part depends on your rendering loop and how you handle drawing)
}



void Butin::UpdateButtonHoverState(const sf::Event& event)
{
    // Update button hover state
    m_isExitButtonHovered = m_exitButton.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
    m_isLaunchgameButtonHovered = m_lauchgameButton.getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
}

void Butin::UpdateButtonSelectionState()
{
    // Update button selection state
    m_isExitButtonSelected = m_isExitButtonHovered;
    m_isLaunchgameButtonSelected = m_isLaunchgameButtonHovered;
}

void Butin::HandleMousePressed(const sf::Event& event)
{
    // Handle mouse button press events
    bool isMouseLeftButtonPressed = event.mouseButton.button == sf::Mouse::Left;
    if (isMouseLeftButtonPressed)
    {
        if (m_isExitButtonSelected)
            m_isExitButtonPressed = true;
        else if (m_isLaunchgameButtonSelected){
            m_isLaunchgameButtonPressed = true;
            m_currentRound = 1;
        }
        // Add more handling if needed
        else if (m_isGameStarted /*&& !m_isPlayerTurn*/) 
            doPlayerTurn(event.mouseButton);    
    
        else if (m_isGameStarted && m_isLaunchgameButtonPressed)
            {     processMouseClick(event.mouseButton);
                  m_boardNeedUpdate = true;}  
    }
}

void Butin::processMouseClick(const sf::Event::MouseButtonEvent &event) {
    // Get board size and dimensions
    auto width = static_cast<float>(m_context->m_window->getSize().x);
    auto height = static_cast<float>(m_context->m_window->getSize().y);
    auto backgroundBoardWidth = width - 10.f;
    auto backgroundBoardHeight = height - 110.f;
    auto cellWidth = (backgroundBoardWidth - 10.f) / BOARD_SIZE;
    auto cellHeight = (backgroundBoardHeight - 10.f) / BOARD_SIZE;

    // Convert mouse click to board coordinates
    if (event.x < 8 || event.x > 480 || event.y < 8 || event.y > 480) return;

    sf::Vector2f boardPos = m_context->m_window->mapPixelToCoords(sf::Vector2i(event.y, event.x));
    const float boardOriginX = 5.f; // Margin from the left
    const float boardOriginY = 5.f; // Margin from the top
    
    int boardX = static_cast<int>((boardPos.x - boardOriginX) / cellWidth);
    int boardY = static_cast<int>((boardPos.y - boardOriginY) / cellHeight);

    // Check if it's the first round
    if (m_currentRound == 1) {
        performFirstRoundAction(boardX, boardY);
        m_currentRound++;
    } else {
        // Subsequent rounds
        std::cout<<"before if"<<std::endl;
        std::cout<<boardX<<std::endl;
        std::cout<<boardY<<std::endl;
        std::cout<<"---------------------------------"<<std::endl;
        if (!isYellowPieceSelected(boardX, boardY)) {
            std::cout<<"before slect yellow piece"<<std::endl;
            selectYellowPiece(boardX, boardY);
            std::cout<<"after slect yellow piece"<<std::endl;
            std::cout<<selectedPieceX<<std::endl;
            std::cout<<selectedPieceY<<std::endl;
        } else {
            if (isValidJumpSelected(selectedPieceX, selectedPieceY, boardX, boardY)) {
                performJump(selectedPieceX, selectedPieceY, boardX, boardY);
                selectedPieceX = -1;
                selectedPieceY = -1;
                //if (!additionalJumpsAvailable(boardX, boardY)) {
                  //  nextPlayerTurn();
                //}
            }
             else {
                clearMoveHighlights();
                showPossibleJumps(selectedPieceX, selectedPieceY);
            }
        }
    }
}
bool Butin::isWithinBoard(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

void Butin::performFirstRoundAction(int x, int y) {
    std::cout << "Attempting to remove piece at x: " << x << ", y: " << y << std::endl;
    //printBoardState();
    Piece* selectedPiece = m_board.get()->getValueAt(x, y);

    if (selectedPiece && selectedPiece->getColor() == sf::Color::Yellow) {
        std::cout << "Removing yellow piece at x: " << y << ", y: " << x << std::endl;
        m_board.get()->setValueAt(x, y, Piece(x, y, nullptr, sf::Color::Transparent, ' '));
        UpdateBoard();
    } else {
        std::cout << "No yellow piece found at x: " << x << ", y: " << y << std::endl;
    }
}


void Butin::printBoardState() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            Piece* piece = m_board.get()->getValueAt(x, y);
            if (piece) {
                if (piece->getColor() == sf::Color::Yellow) std::cout << "Y ";
                else if (piece->getColor() == sf::Color::Red) std::cout << "R ";
                else if (piece->getColor() == sf::Color::Black) std::cout << "B ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}



void Butin::doPlayerTurn(const sf::Event::MouseButtonEvent &event) {
    // Check if the game has started
    if (m_isGameStarted) {
        // Handle the logic based on the mouse click
        processMouseClick(event);
        std::cout<<m_currentRound<<std::endl;
        std::cout<<m_currentPlayerIndex<<std::endl;
    

        // Additional turn-based logic can be added here
        // For example, checking for game over conditions, updating game state, etc.
    }
}



bool Butin::isYellowPieceSelected(int x, int y) {
    // chck the coordinates are within the board's bounds
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >=BOARD_SIZE) {
        return false;
    }

    // Get the piece at the specified coordinates
    Piece* selectedPiece = m_board.get()->getValueAt(x, y);
    
    // Check if the piece is not null and its color is yellow
    return ( selectedPiece->getColor() == sf::Color::Yellow);
}


std::vector<std::pair<int, int>> Butin::getPossibleMoves(Board& board, int currentX, int currentY) {
    std::vector<std::pair<int, int>> moves;

    // Directions in which a piece can move: vertical, horizontal, and diagonal
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (const auto& dir : directions) {
        int nextX = currentX + dir.first;
        int nextY = currentY + dir.second;

        // Check if the next position is within the board boundaries and occupied
        if (isWithinBoard(nextX, nextY) && board.getValueAt(nextX, nextY)->getColor() != sf::Color::Transparent) {
            // Jump position
            int jumpX = nextX + dir.first;
            int jumpY = nextY + dir.second;

            // Check if the jump position is within the board and is empty (transparent)
            if (isWithinBoard(jumpX, jumpY) && board.getValueAt(jumpX, jumpY)->getColor() == sf::Color::Transparent) {
                moves.push_back(std::make_pair(jumpX, jumpY));
            }
        }
    }

    return moves;
}




void Butin::nextPlayerTurn() {
    // Increment the index to switch to the next player
    m_currentPlayerIndex = (m_currentPlayerIndex + 1) % m_players.size();

    // Increase the round number every time a player finishes their turn
    m_currentRound++;

    // You can add any additional logic here that needs to be executed at the start of a new player's turn
}


void Butin::closeWindow() const
{
    // Close the game window
    m_context->m_states->PopAll();
    m_context->m_window->close();
}


// Assuming your cell is represented by an sf::RectangleShape
// and you have a method like 'getRectangleShapeAt(int x, int y)' to get the cell shape

void Butin::showPossibleJumps(int x, int y) {
    Piece* selectedPiece = m_board.get()->getValueAt(y, x); // if your board cells are stored as board[y][x]
    if (selectedPiece && selectedPiece->getColor() == sf::Color::Yellow) {
        auto possibleMoves = this->getPossibleMoves(*m_board, y, x); // Notice the order of y and x
        for (const auto& move : possibleMoves) {
            highlightCell(move.second, move.first); // Swap move.first and move.second if needed
        }
    }
}


void Butin::highlightCell(int x, int y) {
    sf::RectangleShape& cell = getRectangleShapeAt(x, y);
    cell.setFillColor(sf::Color::Green);
}

void Butin::clearMoveHighlights() {
    
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            resetCellAppearance(y, x);
        }
    }
}

void Butin::resetCellAppearance(int x, int y) {
    sf::RectangleShape& cell = getRectangleShapeAt(x, y);
    cell.setFillColor((x + y) % 2 == 0 ? WHITECELL_COLOR : BLACKCELL_COLOR);
}

sf::RectangleShape& Butin::getRectangleShapeAt(int x, int y) {
    // Return the rectangle shape representing the cell at coordinates (x, y)
    // You need to implement this based on how you've stored your cells
    return m_boardCell[x][y];
}

bool Butin::isValidJumpSelected(int startX, int startY, int endX, int endY) {
    Piece* selectedPiece = m_board.get()->getValueAt(startX, startY);
    if (!selectedPiece || selectedPiece->getColor() != sf::Color::Yellow) {
        return false;
    }

    auto possibleMoves = this->getPossibleMoves(*m_board, startX, startY);
    for (const auto& move : possibleMoves) {
        if (move.first == endX && move.second == endY) {
            return true;
        }
    }

    return false;
}

void Butin::performJump(int startX, int startY, int endX, int endY) {
    // Check if jump is valid before performing
    if (!isValidJumpSelected(startX, startY, endX, endY)) {
        std::cout << "Invalid jump attempt from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")" << std::endl;
        return;
    }

    // Perform the jump
    Piece* piece = m_board.get()->getValueAt(startX, startY);
    m_board.get()->setValueAt(endX, endY, Piece(endX, endY, nullptr, sf::Color::Yellow, 'Y'));
    m_board.get()->setValueAt(startX, startY, Piece(startX, startY, nullptr, sf::Color::Transparent, ' '));
    UpdateBoard();
}


bool Butin::additionalJumpsAvailable(int x, int y) {
    // Directions: Up, Down, Left, Right, and four Diagonals
    const std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for (const auto& dir : directions) {
        int nextX = x + dir.first * 2;
        int nextY = y + dir.second * 2;

        if (isValidJump(x, y, nextX, nextY)) {
            return true;
        }
    }

    return false;
}

bool Butin::isValidJump(int startX, int startY, int endX, int endY) {
    // Check bounds
    if (endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
        return false;
    }

    // Midpoint coordinates
    int midX = (startX + endX) / 2;
    int midY = (startY + endY) / 2;

    // Get the pieces
    Piece* startPiece = m_board.get()->getValueAt(startX, startY);
    Piece* midPiece = m_board.get()->getValueAt(midX, midY);
    Piece* endPiece = m_board.get()->getValueAt(endX, endY);

    // Check if start piece is yellow, mid piece is not empty and not yellow, end piece is empty
    if (startPiece && startPiece->getColor() == sf::Color::Yellow &&
        midPiece && midPiece->getColor() != sf::Color::Yellow &&
        (!endPiece || endPiece->getColor() == sf::Color::Transparent)) {
        return true;
    }

    return false;
}
void Butin::selectYellowPiece(int x, int y) {
    Piece* piece = m_board.get()->getValueAt(x, y);
    if (piece && piece->getColor() == sf::Color::Yellow) {
        selectedPieceX = x;
        selectedPieceY = y;
    }
}
