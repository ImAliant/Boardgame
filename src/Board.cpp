#include "../include/Board.hpp"
#include "../include/CheckersPiece.hpp"

#include <iostream>
#include <vector>
#include <tuple>

Board::Board( const GameType type, std::vector<Player*> players):
      type{type}, players{players} 
    {
        std::tie(height, width) = initDimensions(type);
        std::cout << "Board::Board()" << std::endl;
        init();
        
    }


std::tuple<int,int> Board::initDimensions(GameType type)
{
    height = 0;
    width = 0;
    switch ((type))
    {
    case GameType::JEU1:
        break;
    case GameType::CHECKERS:
        height = 10;
        width = 10;
        break;
    case GameType::JEU3:
        break;
    default: //TODO: HANDLE unknown game type
        
        break;
    }
    return std::make_tuple(height, width);
}

std::vector<Player*> Board::initPlayersVector(GameType type)
{
    std::vector<Player*> players;
    size_t nbPlayers = 0;

    switch ((type))
    {
    case GameType::JEU1:
        break;
    case GameType::CHECKERS:
        nbPlayers = 2;
        break;
    case GameType::JEU3:
        break;
    default:
        break;
    }
    return players;
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
                setValueAt(i, j, std::unique_ptr<CheckersPiece>(new CheckersPiece(i, j, *(players[0]))).release());
            } else if(i > 5 && (i + j) % 2 == 1) {
                setValueAt(i, j, std::unique_ptr<CheckersPiece>(new CheckersPiece(i, j, *(players[1]))).release());
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

CheckersPiece* Board::getPieceAt(int x, int y) const
{
    return board[x][y];
}


std::vector<Player*> Board::getPlayers() const
{
    return players;
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