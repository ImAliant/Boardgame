#include "game/Game.hpp"
#include "game/bulltricker/BulltrickerBoard.hpp"

Game::Game() {}

std::shared_ptr<Board> Game::GetBoard() const
{
    return board;
}

void Game::InitPlayers()
{
    AddPlayer(std::make_shared<Player>());
    AddPlayer(std::make_shared<Player>());
}

void Game::AddPlayer(std::shared_ptr<Player> player)
{
    players.push_back(player);
}

void Game::MovePiece(const coord_t from, const coord_t to) const
{
    board->MovePiece(from, to);
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