#include "player/Player.hpp"

int Player::idCounter = 0;

Player::Player()
{
    id = idCounter++;
    score = 0;
}

int Player::GetId() const
{
    return id;
}

int Player::GetScore() const
{
    return score;
}