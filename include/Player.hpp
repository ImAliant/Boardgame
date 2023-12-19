#pragma once

#include <iostream>

class Player
{
    private:
        int m_id;
        static int m_idCounter;
    public:
        explicit Player();
        ~Player();

        std::string ToString() const;

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

        int GetId() const;
};