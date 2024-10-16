#include "game/Game.hpp"
#include "game/checkers/CheckersBoard.hpp"

Game::Game()
{
    Init();
}

void Game::Init()
{
    board = std::make_shared<CheckersBoard>();
}

std::shared_ptr<Board> Game::GetBoard() const
{
    return board;
}