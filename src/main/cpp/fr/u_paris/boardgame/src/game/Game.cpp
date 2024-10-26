#include "game/Game.hpp"

Game::Game(): state{std::make_shared<GameState>()}{}

void Game::Start()
{
    state->Start();
}

void Game::InitPlayers()
{
    AddPlayer(std::make_shared<Player>());
    AddPlayer(std::make_shared<Player>());
}

void Game::SelectPiece(const coord_t coord)
{
    std::shared_ptr<Piece> piece = board->GetPiece(coord);
    if (piece == nullptr)
    {
        throw std::invalid_argument("No piece at this position");
    }

    state->SelectPiece(piece);
    piece->SetPossibleMoves(board);
    state->SetMovesToDisplay(piece->GetPossibleMoves());
}

void Game::MovePiece(const coord_t to) const
{
    if (!state->IsPieceSelected()) 
    {
        throw std::invalid_argument("No piece selected");
    }

    if (!IsMovePossible(to))
    {
        throw std::invalid_argument("Move is not possible");
    }
    auto piece = state->GetSelectedPiece();

    board->MovePiece(piece->GetCoord(), to);
}

bool Game::IsMovePossible(const coord_t to) const
{
    if (!board->IsInBoard(to) 
    || !board->IsEmpty(to)
    || !state->IsPieceSelected()) return false;

    auto moves = state->GetMovesToDisplay();

    for (auto move: moves)
    {
        if (move->GetTo() == to)
        {
            return true;
        }
    }

    return false;
}

void Game::DeselectPiece()
{
    state->DeselectPiece();
    state->ClearCurrentMoves();
}

void Game::AddPlayer(std::shared_ptr<Player> player)
{
    players.push_back(player);
}

std::shared_ptr<Board> Game::GetBoard() const
{
    return board;
}

std::vector<std::shared_ptr<Player>> Game::GetPlayers() const
{
    return players;
}

std::shared_ptr<Player> Game::GetPlayer(const int id) const
{
    if (id < 0 || id >= players.size())
    {
        return nullptr;
    }

    return players[id];
}

std::shared_ptr<GameState> Game::GetState() const
{
    return state;
}