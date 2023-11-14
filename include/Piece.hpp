#ifndef _PIECE
#define _PIECE

#include "Player.hpp"

class Piece
{
    public:
        explicit Piece(int x, int y, Player& player): x{x}, y{y}, owner{player} {}
        virtual ~Piece() = default;

    protected:
        virtual int getX() const {
            return x;
        }
        virtual int getY() const {
            return y;   
        }
        virtual Player& getPlayer() const {
            return owner;
        }

    private:
        int x;
        int y;
        Player& owner;
};

#endif