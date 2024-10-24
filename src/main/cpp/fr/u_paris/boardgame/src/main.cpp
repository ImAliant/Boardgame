#include <iostream>

#include "game/Game.hpp"
#include "game/GameFactory.hpp"
#include "constants/Constants.hpp"
#include "game/checkers/CheckersPiece.hpp"
#include "game/checkers/CheckersBoard.hpp"

using namespace Constants::Game::types;
using namespace Constants::Game::Player;

int main() {
    std::shared_ptr<Game> g = GameFactory::CreateGame(CHECKERS);
    std::shared_ptr<CheckersBoard> board = std::dynamic_pointer_cast<CheckersBoard>(g.get()->GetBoard());
    std::cout << *board << std::endl;

    std::shared_ptr<CheckersPiece> p = std::dynamic_pointer_cast<CheckersPiece>(board->GetPiece(coord_t{3, 0}));
    p->Upgrade();
    p->SetPossibleMoves(board);

    std::vector<std::shared_ptr<Move>> moves = p->GetPossibleMoves();
    std::cout << "Possible moves for " << *p << std::endl;
    for (auto move: moves)
    {
        std::cout << *move << std::endl;
    }

    /* int x = 0;
    int y = 0;

    std::cin >> x >> y;
    coord_t c1{x, y};
    board->RemovePiece(c1);

    std::cout << *board << std::endl;

    std::cin >> x >> y;
    coord_t c2{x, y};
    board->RemovePiece(c2);

    std::cout << *board << std::endl;

    std::cin >> x >> y;
    coord_t c3{x, y};
    std::shared_ptr<ButinPiece> p = std::dynamic_pointer_cast<ButinPiece>(board->GetPiece(c3));

    p->SetPossibleMoves(board);
    std::vector<std::shared_ptr<Move>> moves = p->GetPossibleMoves();
    std::cout << "Possible moves for " << p.get()->GetCoord().first << ", " << p.get()->GetCoord().second << std::endl;
    for (auto move: moves)
    {
        std::cout << *move << std::endl;
    } */

    /* const coord_t coordB{4, 2};
    const coord_t coordW(5, 3);
    board->SetPiece(coordB, std::make_shared<CheckersPiece>(coordB, 'B'));
    board->SetPiece(coordW, std::make_shared<CheckersPiece>(coordW, 'W'));

    std::cout << *board << std::endl;

    std::shared_ptr<CheckersPiece> p = std::dynamic_pointer_cast<CheckersPiece>(board->GetPiece(coordB));
    p->SetPossibleMoves(board);

    std::vector<std::shared_ptr<Move>> moves = p->GetPossibleMoves();
    std::cout << "Possible moves for " << p.get()->GetCoord().first << ", " << p.get()->GetCoord().second << std::endl;
    for (auto move: moves)
    {
        std::cout << *move << std::endl;
    } */

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