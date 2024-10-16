#include "game/bulltricker/Bulltricker.hpp"
#include "game/bulltricker/BulltrickerBoard.hpp"

Bulltricker::Bulltricker(): Game() {
    Init();
}

void Bulltricker::Init()
{
    board = std::make_shared<BulltrickerBoard>();
}