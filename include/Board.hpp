#ifndef _BOARD
#define _BOARD

#include <memory>

#include "GameType.hpp"
#include "CheckersPiece.hpp"
#include "Player.hpp"

class Game;

class Board
{
    public:
        explicit Board(const int height, const int width, const GameType type, Player& player1, Player& player2);
        virtual ~Board();

        void init();
        void initCheckersBoard();

        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        int getHeight() const;
        int getWidth() const;
    private:
        const int height;
        const int width;
        const GameType type;

        Player player1;
        Player player2;

        // TODO : a modififer pour utiliser des pointeurs intelligents
        CheckersPiece* board[10][10];
        void setValueAt(int x, int y, CheckersPiece* value) {
            this->board[x][y] = value;
        }
};

#endif