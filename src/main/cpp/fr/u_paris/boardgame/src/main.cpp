#include <iostream>

#include "game/Game.hpp"

int main() {
    Game g;

    std::cout << *g.GetBoard() << std::endl;

    return 0;
}