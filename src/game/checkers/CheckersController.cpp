#include "../../../include/game/checkers/CheckersController.hpp"

CheckersController::CheckersController(std::shared_ptr<Context> context)
    : m_context(context)
{
    m_model = std::make_unique<Checkers>();
    m_view = std::make_unique<CheckersView>();
}

CheckersController::~CheckersController() {}

void CheckersController::Init()
{
    m_context->m_window->setTitle("Les Dames - Diamant/Hamdi");

    m_model->InitPlayers();
    m_model->InitBoard();
    m_model->UpdatePossibleMoves();

    m_view->Init(m_context, *m_model->GetBoard());
}

void CheckersController::ProcessInput() 
{
    sf::Event event;
    
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            CloseWindow();
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

void CheckersController::Update() {
    m_view->RenderButton();

    // On change de couleur la case lorsqu'un pion est sélectionné
    if (m_model->IsPieceSelected() && !m_view->HasHighLightedCell())
    {
        m_view->HighlightCell(m_model->GetSelectedPiece(), sf::Color::Yellow);
        auto possibleMoves = m_model->GetPossibleMoves(m_model->GetSelectedPiece().first, m_model->GetSelectedPiece().second);
        //auto possibleCaptures = m_model->GetPossibleCaptures(m_model->GetSelectedPiece().first, m_model->GetSelectedPiece().second);
        m_view->HighlightPossibleMoves(possibleMoves/*, possibleCaptures*/);
        m_view->UpdateFlag(m_view->HasHighLightedCell(), true);
    }
    if (m_model->IsSelectedPieceChanged() && 
        m_model->GetLastSelectedPiece().first != -1 && 
        m_model->GetLastSelectedPiece().second != -1 &&
        m_model->GetLastSelectedPiece() != m_model->GetSelectedPiece())
    {
        m_view->RemoveHighlightCell(m_model->GetLastSelectedPiece());
        auto lastPossibleMoves = m_model->GetLastPossibleMoves();
        // debug 
        std::cout << "lastPossibleMoves: " << std::endl;
        for (const auto& [x, y]: lastPossibleMoves)
        {
            std::cout << x << ", " << y << std::endl;
        }
        //  
        m_view->RemoveHighlightPossibleMoves(lastPossibleMoves);
        m_model->ResetSelectedPieceFlag();
        m_view->UpdateFlag(m_view->HasHighLightedCell(), false);
    }
    if (m_model->IsBoardNeedUpdate())
    {
        m_view->UpdateBoard(*m_model->GetBoard());
        m_model->ResetBoardNeedUpdateFlag();
    }

    if (m_view->IsLaunchgameButtonPressed())
    {
        Start();
    }

    if (m_view->IsExitButtonPressed())
    {
        CloseWindow();
    }
}

void CheckersController::Draw() {
    m_view->Draw(*m_context->m_window);
}

void CheckersController::Start() {
    m_view->UpdateFlag(m_view->IsLaunchgameButtonPressed(), false);
    m_view->HideLaunchgameButton();
    m_model->GameStart();

    // TODO: random player

    // update possible moves
    m_model->UpdatePossibleMoves();
}

void CheckersController::UpdateButtonHoverState(const sf::Event& event) {
    bool isExitHovered = m_view->GetExitButton().getGlobalBounds().contains(
        static_cast<float>(event.mouseButton.x), 
        static_cast<float>(event.mouseButton.y)
    );

    bool isLaunchgameHovered = m_view->GetLaunchgameButton().getGlobalBounds().contains(
        static_cast<float>(event.mouseButton.x), 
        static_cast<float>(event.mouseButton.y)
    );

    m_view->UpdateFlag(m_view->IsExitButtonHovered(), isExitHovered);
    m_view->UpdateFlag(m_view->IsLaunchgameButtonHovered(), isLaunchgameHovered);
}

void CheckersController::UpdateButtonSelectionState() {
    bool isExitSelected = m_view->GetExitButton().getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x), 
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y)
    );

    bool isLaunchgameSelected = m_view->GetLaunchgameButton().getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).x), 
        static_cast<float>(sf::Mouse::getPosition(*m_context->m_window).y)
    );

    m_view->UpdateFlag(m_view->IsExitButtonSelected(), isExitSelected);
    m_view->UpdateFlag(m_view->IsLaunchgameButtonSelected(), isLaunchgameSelected);
}

void CheckersController::HandleMousePressed(const sf::Event& event) {
    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;

    if (isMousePressed)
    {
        if (m_view->IsLaunchgameButtonSelected())
            m_view->UpdateFlag(m_view->IsLaunchgameButtonPressed(), true);
        if (m_view->IsExitButtonSelected())
            m_view->UpdateFlag(m_view->IsExitButtonPressed(), true);
        if (m_model->IsGameStarted())
        {
            auto x = event.mouseButton.x;
            auto y = event.mouseButton.y;

            using namespace CheckersConstants;
            if (x < CLICKABLE_ZONE.first || x > CLICKABLE_ZONE.second || y < CLICKABLE_ZONE.first || y > CLICKABLE_ZONE.second)
                return;

            std::pair<int, int> coord = m_view->GetBoardCoord(x, y);
        
            m_model->Turn(coord);
        }
    }
}

void CheckersController::CloseWindow() const {
    m_context->m_states->PopAll();
    m_context->m_window->close();
}



