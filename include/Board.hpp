#ifndef _BOARD
#define _BOARD

#include <memory>

#include "GameType.hpp"
#include "CheckersPiece.hpp"
#include "Player.hpp"
#include <vector>

class Game;

class Board
{
    friend class checkersGame;
    public:
        explicit Board(const GameType type, std::vector<Player*> players);
        virtual ~Board();

        void init();
        void initCheckersBoard();
        std::vector<Player*> initPlayersVector(GameType type);
        std::tuple<int,int> initDimensions(GameType type);
        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        int getHeight() const;
        int getWidth() const;
        std::unique_ptr<CheckersPiece> getPieceAt(int x, int y) const;
        std::vector<Player*> getPlayers() const;
        void setValueAt(int x, int y, CheckersPiece* value) {
            this->board[x][y] = value;
        }
    private:
        int height;
        int width;
        const GameType type;
        
        const std::vector<Player*> players;

    protected:    
        // TODO : a modififer pour utiliser des pointeurs intelligents
        CheckersPiece* board[10][10];
        
};

#endif