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
        int getPlayerId() const;
    private:
        Players player;
        int id; 
        static int idCount;
};

#endif