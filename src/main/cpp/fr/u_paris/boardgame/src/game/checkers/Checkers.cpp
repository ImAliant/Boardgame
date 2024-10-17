#include "game/checkers/Checkers.hpp"
#include "game/checkers/CheckersBoard.hpp"
#include "game/checkers/CheckersPiece.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::Checkers;
using namespace Constants::Game::Player;

Checkers::Checkers(): Game() {
    Init();
}

void Checkers::Init()
{
    board = std::make_shared<CheckersBoard>();
    InitPlayers();
}

void Checkers::InitPlayers()
{
    Game::InitPlayers();
    DistributePieces();
}

void Checkers::DistributePieces()
{   
    std::vector<std::shared_ptr<Player>> players = GetPlayers();

    // On cast le board en CheckersBoard pour accéder à ses méthodes
    auto checkers_board = std::dynamic_pointer_cast<CheckersBoard>(board);
    for (int i{0}; i < checkers_board.get()->GetHeight(); i++)
    {
        for (int j{0}; j < checkers_board.get()->GetWidth(); j++)
        {
            // On cast la piece en CheckersPiece pour accéder à ses méthodes
            auto piece = std::dynamic_pointer_cast<CheckersPiece>(checkers_board.get()->GetPiece(coord_t{i, j}));
            if (piece == nullptr)
            {
                continue;
            }
            
            if (piece.get()->GetSymbol() == BLACK_PIECE_SYMBOL) {
                players[PLAYER_ONE]->AddPiece(piece);
            }
            else {
                players[PLAYER_TWO]->AddPiece(piece);
            }
        }
    }
}