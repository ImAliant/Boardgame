#include "../../../include/game/Butin/ButinController.hpp"


ButinController::ButinController(std::shared_ptr<Context> context)
    : m_context(context)
{
    m_model = std::make_unique<Butin>();
    m_view = std::make_unique<ButinView>();
}

ButinController::~ButinController() {}

void ButinController::Init()
{
    m_context->m_window->setTitle("Butin - Diamant/Hamdi");

    m_model->Init();
    m_view->Init(m_context, *m_model->GetBoard());
}

void ButinController::ProcessInput() 
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
void ButinController::Update(){
    m_view->Render();
    if (m_model->IsPieceSelected() && !m_view->HasHighLightedCell())
    {
        m_view->HighlightCell(m_model->GetSelectedPiece(), sf::Color::Blue);
        auto possibleMoves = m_model->GetPossibleMoves(m_model->GetSelectedPiece().first, m_model->GetSelectedPiece().second);
        m_view->HighlightPossibleMoves(possibleMoves);
        m_view->NeedHighlight();
    }
    if (m_model->IsSelectedPieceChanged() && 
        m_model->GetLastSelectedPiece().first != -1 && 
        m_model->GetLastSelectedPiece().second != -1 &&
        m_model->GetLastSelectedPiece() != m_model->GetSelectedPiece())
    {
        m_view->RemoveHighlightCell(m_model->GetLastSelectedPiece());
        auto lastPossibleMoves = m_model->GetPossibleMoves(m_model->GetLastSelectedPiece().first, m_model->GetLastSelectedPiece().second);
        m_view->RemoveHighlightPossibleMoves(lastPossibleMoves);
        m_model->ResetSelectedPieceFlag();
        m_view->RemoveHighlight();
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

void ButinController::Draw() {
    m_view->Draw(*m_context->m_window);
}

void ButinController::Start() {
    m_view->HideLaunchgameButton();
    m_model->GameStart();
    m_view->PrintCurrentPlayer(m_model->GetCurrentPlayer());

    m_view->ResetLaunchPressedFlag();
}

void ButinController::UpdateButtonHoverState(const sf::Event& event) {
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

void ButinController::UpdateButtonSelectionState() {
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

void ButinController::HandleMousePressed(const sf::Event& event) {
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

            using namespace ButinConstants;
            if (x < CLICKABLE_ZONE.first || x > CLICKABLE_ZONE.second || y < CLICKABLE_ZONE.first || y > CLICKABLE_ZONE.second)
                return;
            std::cout << "hola" << std::endl;
            std::pair<int, int> coord = m_view->GetBoardCoord(x, y);
            std::cout << coord.first << " " << coord.second << std::endl;
        
            m_model->Turn(coord);
        }
    }
}

void ButinController::CloseWindow() const {
    m_context->m_states->PopAll();
    m_context->m_window->close();
}
