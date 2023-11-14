#include "../include/CheckersGame.hpp"

#include <iostream>

CheckersGame::CheckersGame() 
{
    std::cout << "CheckersGame::CheckersGame()" << std::endl;
}

// boucle du jeu
void CheckersGame::run() 
{
    Player player1{Players::P1};
    Player player2{Players::P2};
    Board board{10, 10, GameType::CHECKERS, player1, player2};

    std::cout << board << std::endl;

    std::vector<Player> players{player1, player2};

    startGame(board, players);
}

void CheckersGame::startGame(Board& board, std::vector<Player>& players)
{
    bool isRunning = true;
    int turn{0};
    while (isRunning)
    {
        if (turn % 2 == 0) playTurn(board, players[0]);
        else playTurn(board, players[1]);

        // TODO :check if game is over
            // TODO : if yes, check who won
                // TODO : if yes, display winner
                // TODO : if no, display draw
            // TODO : isRunning = false;

        turn++;
    }
}

void CheckersGame::playTurn(Board& board, Player& player)
{
    // TODO : movement choice
    // TODO : check if movement is valid
    // TODO : check if a piece is eaten
        // TODO : if yes, check if another piece can be eaten
    // TODO : check if a piece is promoted
}

CheckersGame::~CheckersGame() 
{
    std::cout << "CheckersGame::~CheckersGame()" << std::endl;
}