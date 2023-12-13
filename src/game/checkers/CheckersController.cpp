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
    if (m_model->IsPieceSelected() && !m_view->GetHasHighLightedCell())
    {
        m_view->HighlightCell(m_model->GetSelectedPiece(), sf::Color::Yellow);
        auto possibleMoves = m_model->GetPossibleMoves(m_model->GetSelectedPiece().first, m_model->GetSelectedPiece().second);
        m_view->HighlightPossibleMoves(possibleMoves);
        m_view->UpdateFlag(m_view->GetHasHighLightedCell(), true);
    }
    if (m_model->IsSelectedPieceChanged() && 
        m_model->GetLastSelectedPiece().first != -1 && 
        m_model->GetLastSelectedPiece().second != -1 &&
        m_model->GetLastSelectedPiece() != m_model->GetSelectedPiece())
    {
        m_view->RemoveHighlightCell(m_model->GetLastSelectedPiece());
        auto lastPossibleMoves = m_model->GetLastPossibleMoves();
        m_view->RemoveHighlightPossibleMoves(lastPossibleMoves);
        m_model->ResetSelectedPieceFlag();
        m_view->UpdateFlag(m_view->GetHasHighLightedCell(), false);
    }

    if (m_view->GetIsLaunchgameButtonPressed())
    {
        Start();
    }

    if (m_view->GetIsExitButtonPressed())
    {
        CloseWindow();
    }
}

void CheckersController::Draw() {
    m_view->Draw(*m_context->m_window);
}

void CheckersController::Start() {
    m_view->UpdateFlag(m_view->GetIsLaunchgameButtonPressed(), false);
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

    m_view->UpdateFlag(m_view->GetIsExitButtonHovered(), isExitHovered);
    m_view->UpdateFlag(m_view->GetIsLaunchgameButtonHovered(), isLaunchgameHovered);
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

    m_view->UpdateFlag(m_view->GetIsExitButtonSelected(), isExitSelected);
    m_view->UpdateFlag(m_view->GetIsLaunchgameButtonSelected(), isLaunchgameSelected);
}

void CheckersController::HandleMousePressed(const sf::Event& event) {
    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;

    if (isMousePressed)
    {
        if (m_view->GetIsLaunchgameButtonSelected())
            m_view->UpdateFlag(m_view->GetIsLaunchgameButtonPressed(), true);
        if (m_view->GetIsExitButtonSelected())
            m_view->UpdateFlag(m_view->GetIsExitButtonPressed(), true);
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



