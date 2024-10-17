#include "player/Player.hpp"

int Player::idCounter = 0;

Player::Player()
{
    id = idCounter++;
    score = 0;
}

void Player::AddPiece(std::shared_ptr<Piece> piece)
{
    pieces.push_back(piece);
}

void Player::AddScore(int s)
{
    if (s < 0)
    {
        return;
    }

    score += s;
}

int Player::GetId() const
{
    return id;
}

int Player::GetScore() const
{
    return score;
}

std::vector<std::shared_ptr<Piece>> Player::GetPieces() const
{
    return pieces;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "Player " << player.id << " has a score of " << player.score;
    return os;
}