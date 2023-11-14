#include "../include/Board.hpp"
#include "../include/CheckersPiece.hpp"

#include <iostream>

Board::Board(const int height, const int width, const GameType type, Player& player1, Player& player2):
    height{height}, width{width}, type{type}, player1{player1}, player2{player2} 
    {
        std::cout << "Board::Board()" << std::endl;
        init();
    }

void Board::init()
{
    switch(type) {
        case GameType::JEU1:
            break;
        case GameType::CHECKERS:
            initCheckersBoard();
            break;
        case GameType::JEU3:
            break;
    }
}

void Board::initCheckersBoard()
{
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++)
        {
            if(i < 4 && (i + j) % 2 == 1) {
                setValueAt(i, j, std::unique_ptr<CheckersPiece>(new CheckersPiece(i, j, player1)).release());
            } else if(i > 5 && (i + j) % 2 == 1) {
                setValueAt(i, j, std::unique_ptr<CheckersPiece>(new CheckersPiece(i, j, player2)).release());
            } else {
                board[i][j] = nullptr;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    os << "  ";
    for (int i = 0; i < board.width; i++) 
    {
        os << i << " "; 
    }
    os << std::endl;
    os << "  ";
    for (int i = 0; i < board.width*2; i++) 
    {
        os << "_";
    }
    os << std::endl;

    for (int i = 0; i < board.height; i++) 
    {
        os << i << "|";
        for (int j = 0; j < board.width; j++) 
        {
            if (board.board[i][j] == nullptr) 
            {
                os << "* ";
            } 
            else 
            {
                os << board.board[i][j]->getSymbol() << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

Board::~Board()
{
    std::cout << "Board::~Board()" << std::endl;
    // Nettoyer le tableau
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++)
        {
            if(board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
    }
}

int Board::getHeight() const
{
    return height;
}

int Board::getWidth() const
{
    return width;
}