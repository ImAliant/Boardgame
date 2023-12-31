#include "../../../include/game/checkers/CheckersController.hpp"
#include "../../../include/GameChoice.hpp"

CheckersController::CheckersController(std::shared_ptr<Context> context): 
    Controller{context, std::make_unique<Checkers>(), std::make_unique<CheckersView>()}
{}

void CheckersController::SetWindowTitle() const
{
    m_context->m_window->setTitle(WindowConstants::CHECKERS_TITLE);
}

void CheckersController::PrintAndResetPlayer() const
{
    m_view->PrintCurrentPlayer(m_model->GetCurrentPlayer());
    m_model->ResetCurrentPlayerChangedFlag();
}

void CheckersController::End() {
    m_view->PrintWinner(m_model->GetWinner());
    
    Controller::End();
}



