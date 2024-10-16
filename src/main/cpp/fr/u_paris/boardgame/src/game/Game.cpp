#include "game/Game.hpp"
#include "game/butin/ButinBoard.hpp"

Game::Game()
{
    Init();
}

void Game::Init()
{
    board = std::make_shared<ButinBoard>();
}

std::shared_ptr<Board> Game::GetBoard() const
{
    return board;
}