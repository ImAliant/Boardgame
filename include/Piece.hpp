#ifndef _PIECE
#define _PIECE

#include "Player.hpp"

class Piece
{   
    friend class CheckersGame;
    public:
        explicit Piece(int x, int y, Player& player): x{x}, y{y}, owner{player} {}
        virtual ~Piece() = default;
        virtual Player& getPlayer() const { //car on l'utilise dans la classe CheckersGame
                                            //erreur d'innacessibilité avec protected
            return owner;
        }


    protected:
        virtual int getX() const {
            return x;
        }
        virtual int getY() const {
            return y;   
        }
       

    private:
        int x;
        int y;
        Player& owner;
};

#endif