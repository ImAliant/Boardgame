#include "../include/Player.hpp"

Player::Player(Players player) : player(player) {}

Players Player::getPlayer() const
{
    return player;
}