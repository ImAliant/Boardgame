#include "game/bulltricker/Bulltricker.hpp"
#include "game/bulltricker/BulltrickerBoard.hpp"
#include "game/bulltricker/BulltrickerPiece.hpp"
#include "constants/Constants.hpp"

using namespace Constants::Game::Bulltricker;
using namespace Constants::Game::Player;

Bulltricker::Bulltricker(): Game() {
    Init();
}

void Bulltricker::Init()
{
    board = std::make_shared<BulltrickerBoard>();
    InitPlayers();
}

void Bulltricker::InitPlayers()
{
    Game::InitPlayers();
    DistributePieces();
}

void Bulltricker::Start()
{
    std::cout << "Starting Bulltricker" << std::endl;
}

void Bulltricker::DistributePieces()
{   
    std::vector<std::shared_ptr<Player>> players = GetPlayers();

    // On cast le board en BulltrickerBoard pour accéder à ses méthodes
    auto bulltricker_board = std::dynamic_pointer_cast<BulltrickerBoard>(board);
    for (int i{0}; i < bulltricker_board.get()->GetHeight(); i++)
    {
        for (int j{0}; j < bulltricker_board.get()->GetWidth(); j++)
        {
            // On cast la piece en BulltrickerPiece pour accéder à ses méthodes
            auto piece = std::dynamic_pointer_cast<BulltrickerPiece>(bulltricker_board.get()->GetPiece(coord_t{i, j}));
            if (piece == nullptr)
            {
                continue;
            }
            
            if (piece.get()->IsBlack()) {
                players[PLAYER_ONE]->AddPiece(piece);
            }
            else {
                players[PLAYER_TWO]->AddPiece(piece);
            }
        }
    }
}