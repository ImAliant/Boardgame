#include "game/GameFactory.hpp"
#include "constants/Constants.hpp"

#include "game/checkers/Checkers.hpp"
#include "game/butin/Butin.hpp"
#include "game/bulltricker/Bulltricker.hpp"

using namespace Constants::Game::types;

std::shared_ptr<Game> GameFactory::CreateGame(const int type)
{
    switch (type)
    {
        case CHECKERS:
            return std::make_shared<Checkers>();
        case BUTIN:
            return std::make_shared<Butin>();
        case BULLTRICKER:
            return std::make_shared<Bulltricker>();
        default:
            return nullptr;
    }
}