#include "game/Controller.hpp"

Controller::Controller(std::shared_ptr<Game> game, std::shared_ptr<View> view)
    : game{game}, view{view} {}

void Controller::Start()
{
    game->Start();
}