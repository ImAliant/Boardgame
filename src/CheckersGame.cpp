#include "../include/CheckersGame.hpp"
#include "../include/Player.hpp"

#include <iostream>

CheckersGame::CheckersGame() 
{
    std::cout << "CheckersGame::CheckersGame()" << std::endl;
}

// boucle du jeu
void CheckersGame::run() 
{
    init();
}

void CheckersGame::init() 
{
    initPlayers();
}

void CheckersGame::initPlayers() 
{
    std::cout << "CheckersGame::initPlayers()" << std::endl;
    players.push_back(Player(Players::P1));
    players.push_back(Player(Players::P2));
}

CheckersGame::~CheckersGame() 
{
    std::cout << "CheckersGame::~CheckersGame()" << std::endl;
}