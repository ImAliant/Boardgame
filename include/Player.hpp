#ifndef _PLAYER
#define _PLAYER

enum class Players
{
    P1,
    P2
};

class Player
{
    public:
        explicit Player(Players player);
        ~Player() = default;

        Players getPlayer() const;
    private:
        Players player;
};

#endif