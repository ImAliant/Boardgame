#include "game/checkers/Checkers.hpp"
#include "game/checkers/CheckersBoard.hpp"

Checkers::Checkers(): Game() {
    Init();
}

void Checkers::Init()
{
    board = std::make_shared<CheckersBoard>();
}