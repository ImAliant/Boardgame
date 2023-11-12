#include "../include/CheckersGame.hpp"
#include "../include/CheckersRules.hpp"

#include <iostream>

void CheckersGame::run() {
    std::cout << "CheckersGame::run()" << std::endl;
    rules = std::unique_ptr<CheckersRules>(new CheckersRules());
    rules->isGameFinished();
}

CheckersGame::~CheckersGame() {
    std::cout << "CheckersGame::~CheckersGame()" << std::endl;
}