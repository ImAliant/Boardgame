#pragma once

#include <iostream>

enum class Players
{
    PLAYER_ONE,
    PLAYER_TWO,
    PLAYER_THREE,
    NONE
};

class Player
{
    private:
        Players m_player;
        int m_id;
        static int m_idCounter;
    public:
        explicit Player(Players player);
        ~Player();

        std::string ToString() const;

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

        Players getPlayer() const;
        int getId() const;
};