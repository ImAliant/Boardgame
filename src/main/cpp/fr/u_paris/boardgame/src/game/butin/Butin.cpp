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

void Butin::Start()
{
    std::cout << "Starting Butin" << std::endl;
}

void Butin::Turn()
{
    std::cout << "Turn" << std::endl;
}

bool Butin::IsGameFinished()
{
    return false;
}