#include "../include/Player.hpp"

int Player::idCount = 1;

Player::Player(Players player) : player(player) , id(idCount++){}

Players Player::getPlayer() const
{
    return player;
}
char Player::getPlayerChar() const {
    return (getPlayerId() == 1) ? 'x' : 'o';
}


int Player::getPlayerId() const
{
    return id;
}