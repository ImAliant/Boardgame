#include "../../../include/game/checkers/CheckersController.hpp"
#include "../../../include/GameChoice.hpp"

CheckersController::CheckersController(std::shared_ptr<Context> context)
    : m_context(context)
{
    m_model = std::make_unique<Checkers>();
    m_view = std::make_unique<CheckersView>();
}

CheckersController::~CheckersController() {}

void CheckersController::Init()
{
    m_context->m_window->setTitle(WindowConstants::CHECKERS_TITLE);

    m_model->Init();
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
    m_view->Render();

    // On change de couleur la case lorsqu'un pion est sélectionné
    UpdateHighlight();
    UpdateBoard();
    UpdateCurrentPlayer();
    UpdateButtonPushed();
}

void CheckersController::UpdateHighlight() const
{
    if (m_model->IsPieceSelected() && !m_view->HasHighLightedCell())
    {
        HighlightSelectedPiece();
    }
    else if (m_model->IsSelectedPieceChanged() && 
        m_model->GetLastSelectedPiece().first != -1 && 
        m_model->GetLastSelectedPiece().second != -1 &&
        m_model->GetLastSelectedPiece() != m_model->GetSelectedPiece())
    {
        RemoveHighlightSelectedPiece();
    }
}

void CheckersController::HighlightSelectedPiece() const
{
    const auto& selectedPiece = m_model->GetSelectedPiece();
    const auto& possibleMoves = m_model->GetPossibleMoves(selectedPiece);
    
    m_view->HighlightCell(selectedPiece, sf::Color::Yellow);
    m_view->HighlightPossibleMoves(possibleMoves);
    m_view->NeedHighlight();
}

void CheckersController::RemoveHighlightSelectedPiece() const
{
    const auto& lastSelectedPiece = m_model->GetLastSelectedPiece();
    const auto& lastPossibleMoves = m_model->GetLastPossibleMoves();
    
    m_view->RemoveHighlightCell(lastSelectedPiece);
    m_view->RemoveHighlightPossibleMoves(lastPossibleMoves);
    m_model->ResetSelectedPieceFlag();
    m_view->RemoveHighlight();
}

void CheckersController::UpdateBoard() const
{
    if (m_model->IsBoardNeedUpdate())
    {
        m_view->UpdateBoard(*m_model->GetBoard());
        m_model->ResetBoardNeedUpdateFlag();
    }
}

void CheckersController::UpdateCurrentPlayer() const
{
    if (m_model->IsCurrentPlayerChanged() && !m_model->IsGameFinished())
    {
        m_view->PrintCurrentPlayer(m_model->GetCurrentPlayer());
        m_model->ResetCurrentPlayerChangedFlag();
    }
}

void CheckersController::UpdateButtonPushed()
{
    if (m_view->IsLaunchgameButtonPressed()) Start();

    if (m_view->IsExitButtonPressed()) CloseWindow();
}

void CheckersController::Draw() {
    m_view->Draw(*m_context->m_window);
}

void CheckersController::Start() {
    m_view->HideLaunchgameButton();
    m_model->GameStart();
    m_view->PrintCurrentPlayer(m_model->GetCurrentPlayer());

    m_view->ResetLaunchPressedFlag();
}

void CheckersController::End() {
    m_view->PrintWinner(m_model->GetWinner());
    m_context->m_states->Add(std::make_unique<GameChoice>(m_context), true);
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

    m_view->UpdateExitHoveredFlag(isExitHovered);
    m_view->UpdateLaunchHoveredFlag(isLaunchgameHovered);
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

    m_view->UpdateExitSelectedFlag(isExitSelected);
    m_view->UpdateLaunchSelectedFlag(isLaunchgameSelected);
}

void CheckersController::HandleMousePressed(const sf::Event& event) {
    bool isMousePressed = event.mouseButton.button == sf::Mouse::Left;

    if (isMousePressed)
    {
        if (m_view->IsLaunchgameButtonSelected())
            m_view->LauchButtonPressed();
        if (m_view->IsExitButtonSelected())
            m_view->ExitButtonPressed();
        if (m_model->IsGameStarted())
        {
            auto x = event.mouseButton.x;
            auto y = event.mouseButton.y;

            using namespace GameConstants;
            if (x < CLICKABLE_ZONE.first || x > CLICKABLE_ZONE.second || y < CLICKABLE_ZONE.first || y > CLICKABLE_ZONE.second)
                return;

            std::pair<int, int> coord = m_view->GetBoardCoord(x, y);
        
            m_model->Turn(coord);
        }
        if (m_model->IsGameFinished())
        {
            End();
        }
    }
}

void CheckersController::CloseWindow() const {
    m_context->m_states->PopAll();
    m_context->m_window->close();
}



