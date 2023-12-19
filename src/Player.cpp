#include "../include/Player.hpp"

#include <iostream>

int Player::m_idCounter = 0;

Player::Player()
{
    m_id = m_idCounter++;
}

Player::~Player() {}

std::string Player::ToString() const
{
    return "Player " + std::to_string(m_id);
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << player.ToString();
    return os;
}

int Player::GetId() const
{
    return m_id;
}

