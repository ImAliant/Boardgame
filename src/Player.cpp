#include "../include/Player.hpp"

#include <iostream>

int Player::m_idCounter = 0;

Player::Player(Players player): m_player(player), m_score(0)
{
    m_id = m_idCounter++;
}

Player::~Player() {}

std::string Player::ToString() const
{
    std::string str;
    switch (m_player)
    {
        case Players::PLAYER_ONE:
            str = "PLAYER_ONE";
            break;
        case Players::PLAYER_TWO:
            str = "PLAYER_TWO";
            break;
        case Players::PLAYER_THREE:
            str = "PLAYER_THREE";
            break;
        case Players::NONE:
            str = "NONE";
            break;
    }
    return str;
}

void Player::addScore(int points) {
    m_score += points;
}

int Player::getScore() const {
    return m_score;
}



std::ostream& operator<<(std::ostream& os, const Player& player)
{
    switch (player.getPlayer())
    {
        case Players::PLAYER_ONE:
            os << "PLAYER_ONE";
            break;
        case Players::PLAYER_TWO:
            os << "PLAYER_TWO";
            break;
        case Players::PLAYER_THREE:
            os << "PLAYER_THREE";
            break;
        case Players::NONE:
            os << "NONE";
            break;
    }
    return os;
}

Players Player::getPlayer() const
{
    return m_player;
}

int Player::getId() const
{
    return m_id;
}

