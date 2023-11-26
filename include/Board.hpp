#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "GameType.hpp"
#include "Piece.hpp"

class Piece;

class Board
{
    private:
        int rows = -1;
        int cols = -1;

        std::vector<std::vector<std::unique_ptr<Piece>>> board;
        std::vector<std::shared_ptr<Player>> players;
    public:
        Board() = default;
        explicit Board(GameType gameType, std::vector<std::shared_ptr<Player>> players);
        ~Board();

        friend std::ostream& operator<<(std::ostream& os, const Board& board);

        void init(GameType gameType);
        void initBoard(GameType gameType);
        void initCheckersBoard();

        void fillBoardWithEmptyPieces();
        void setPiecesOnBoard();

        void setDimensions(int rows, int cols);

        Piece *getValueAt(int x, int y) const;
        void setValueAt(int x, int y, const Piece &piece);

        int getRows() const;
        int getCols() const;
};