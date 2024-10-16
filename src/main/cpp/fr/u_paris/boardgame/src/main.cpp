#include <iostream>

#include "game/Game.hpp"
#include "game/GameFactory.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::types;

int main() {
    std::shared_ptr<Game> g = GameFactory::CreateGame(BULLTRICKER);

    std::cout << *(g->GetBoard()) << std::endl;

    return 0;
}