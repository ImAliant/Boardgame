#include "../include/Player.hpp"

int Player::idCount = 0;

Player::Player(Players player) : player(player) , id(id++){}

Players Player::getPlayer() const
{
    return player;
}

int Player::getPlayerId() const
{
    return id;
}