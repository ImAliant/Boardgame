#include <iostream>

#include "game/Game.hpp"
#include "game/GameFactory.hpp"
#include "constants/Constants.hpp"
#include "game/checkers/CheckersPiece.hpp"

using namespace Constants::Game::types;
using namespace Constants::Game::Player;

int main() {
    std::shared_ptr<Game> g = GameFactory::CreateGame(CHECKERS);
    std::cout << *(g.get()->GetBoard()) << std::endl;

    std::shared_ptr<CheckersPiece> p = std::dynamic_pointer_cast<CheckersPiece>(g.get()->GetBoard()->GetPiece({6, 1}));
    p->SetPossibleMoves(g.get()->GetBoard());

    std::vector<std::shared_ptr<Move>> moves = p->GetPossibleMoves();
    for (auto move: moves)
    {
        std::cout << *move << std::endl;
    }

    /* g->MovePiece(coord_t{3,0}, coord_t{4,1});

    std::cout << *(g.get()->GetBoard()) << std::endl; */

    /* std::shared_ptr<Player> p1 = g->GetPlayer(PLAYER_ONE);
    std::cout << *p1 << std::endl;

    std::vector<std::shared_ptr<Piece>> pieces = p1->GetPieces();
    std::cout << "Player 1 has " << pieces.size() << " pieces" << std::endl;

    for (auto piece: pieces)
    {
        const auto& [x, y] = piece.get()->GetCoord();
        std::cout << "Piece at " << x << ", " << y << std::endl;
    } */

    return 0;
}