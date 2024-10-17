#include "game/butin/Butin.hpp"
#include "game/butin/ButinBoard.hpp"

Butin::Butin(): Game() {
    Init();
}

void Butin::Init()
{
    board = std::make_shared<ButinBoard>();
    InitPlayers();
}