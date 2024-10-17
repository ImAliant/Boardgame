#include <iostream>

#include "game/Game.hpp"
#include "game/GameFactory.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::types;
using namespace Constants::Game::Player;

int main() {
    std::shared_ptr<Game> g = GameFactory::CreateGame(CHECKERS);
    std::cout << *(g.get()->GetBoard()) << std::endl;

    std::shared_ptr<Player> p1 = g->GetPlayer(PLAYER_ONE);
    std::cout << *p1 << std::endl;

    std::vector<std::shared_ptr<Piece>> pieces = p1->GetPieces();
    std::cout << "Player 1 has " << pieces.size() << " pieces" << std::endl;

    for (auto piece: pieces)
    {
        const auto& [x, y] = piece.get()->GetCoord();
        std::cout << "Piece at " << x << ", " << y << std::endl;
    }

    return 0;
}