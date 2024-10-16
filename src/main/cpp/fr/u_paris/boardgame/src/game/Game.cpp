#include "game/Game.hpp"
#include "game/bulltricker/BulltrickerBoard.hpp"

Game::Game()
{
    Init();
}

void Game::Init()
{
    board = std::make_shared<BulltrickerBoard>();
}

std::shared_ptr<Board> Game::GetBoard() const
{
    return board;
}