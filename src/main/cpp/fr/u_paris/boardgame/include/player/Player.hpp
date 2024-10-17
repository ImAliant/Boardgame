#pragma once

class Player
{
    private:
        static int idCounter;

        int id;
        int score;
    public:
        explicit Player();
        virtual ~Player() = default;

        int GetId() const;
        int GetScore() const;

        friend std::ostream& operator<<(std::ostream& os, const Player& player);
};