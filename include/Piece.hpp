#ifndef _PIECE
#define _PIECE

#include "Player.hpp"

class Piece
{
    public:
        explicit Piece(int x, int y, Player& player): x{x}, y{y}, player{player} {}
        virtual ~Piece() = default;

    protected:
        virtual int getX() const {
            return x;
        }
        virtual int getY() const {
            return y;   
        }
        virtual Player& getPlayer() const {
            return player;
        }

    private:
        int x;
        int y;
        Player& player;
};

#endif