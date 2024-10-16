#include "game/Game.hpp"
#include "game/bulltricker/BulltrickerBoard.hpp"

Game::Game() {}

std::shared_ptr<Board> Game::GetBoard() const
{
    return board;
}