#include "game/GameState.hpp"

GameState::GameState()
{
    Init();
}

void GameState::Init()
{
    state = NOT_STARTED;
    selectedPiece = nullptr;
    movesToDisplay.clear();
}

void GameState::SelectPiece(const std::shared_ptr<Piece> piece)
{
    if (selectedPiece != nullptr) return;

    selectedPiece = piece;
}

void GameState::DeselectPiece()
{
    if (selectedPiece == nullptr) return;

    selectedPiece = nullptr;
}

void GameState::SetMovesToDisplay(const std::vector<std::shared_ptr<Move>> moves)
{
    if (!movesToDisplay.empty())
    {
        movesToDisplay.clear();
    }

    movesToDisplay = moves;
}

void GameState::ClearCurrentMoves()
{
    movesToDisplay.clear();
}

void GameState::Start()
{
    if (state != NOT_STARTED) return;
    state = STARTED;
}

void GameState::Stop()
{
    if (state != STARTED) return;
    state = FINISHED;
}

bool GameState::IsPieceSelected() const
{
    return selectedPiece != nullptr;
}

State GameState::GetState() const
{
    return state;
}

std::shared_ptr<Piece> GameState::GetSelectedPiece() const
{
    return selectedPiece;
}

std::vector<std::shared_ptr<Move>> GameState::GetMovesToDisplay() const
{
    return movesToDisplay;
}

std::ostream& operator<<(std::ostream& os, const GameState& state)
{
    os << "State: ";
    switch (state.state)
    {
        case NOT_STARTED:
            os << "Not started";
            break;
        case STARTED:
            os << "Started";
            break;
        case FINISHED:
            os << "Finished";
            break;
    }

    os << std::endl;
    os << "Selected piece: ";
    if (state.selectedPiece == nullptr)
    {
        os << "None";
    }
    else
    {
        os << *state.selectedPiece;
    }
    os << std::endl;

    return os;
}