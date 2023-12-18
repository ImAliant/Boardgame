#include <iostream>
#include <random>
#include "../include/Board.hpp"
#include "../include/exception/GameTypeInvalidException.hpp"
#include "../include/exception/InitializationException.hpp"

Board::Board(GameType gameType, std::vector<std::shared_ptr<Player>> players): players(std::move(players))
{
    init(gameType);
}

Board::~Board() {};

void Board::init(GameType gameType)
{
    try 
    {
        switch (gameType)
        {
            case GameType::BUTIN:
                setDimensions(8, 8);
                break;
            case GameType::CHECKERS:
                setDimensions(10, 10);
                break;
            case GameType::JEU3:
                //setDimensions(?, ?);
                break;
            default:
                throw GameTypeInvalidException("GameType is invalid\n");
                break;
        }
    }
    catch (GameTypeInvalidException &e)
    {
        std::cout << e.what() << std::endl;
    }

    initBoard(gameType);
}

void Board::initBoard(GameType gameType)
{ 
    if (rows < 0 || cols < 0)
    {
        throw InitializationException("The size of the board is invalid\n");
    }

    // initialize the piece on the board
    if (gameType == GameType::CHECKERS)
    {
        initCheckersBoard();
    }else if (gameType == GameType::BUTIN)
    {
        initButinBoard();
        std::cout << "init butin board" << std::endl;
    }
}

void Board::initCheckersBoard()
{
    // initialize the board with empty pieces
    fillBoardWithEmptyPieces();

    // Set the pieces on the board
    setPiecesOnBoard();
}
void Board::initButinBoard()
{
    fillBoardWithEmptyPieces();
    std::cout << " inside init butin board" << std::endl;
   setButinPiecesOnBoard();
}
   
void Board::setButinPiecesOnBoard()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, rows * cols - 1);

    int yellowCount = 34, redCount = 20, blackCount = 10;
    while (yellowCount + redCount + blackCount > 0) {
        int position = dis(gen);
        int x = position / cols;
        int y = position % cols;

        // Check if the position is already occupied
        if (getValueAt(x, y)->getColor() == sf::Color::Transparent) { // Assuming Transparent indicates an empty spot
            if (yellowCount > 0) {
                setValueAt(x, y, Piece(x, y, nullptr, sf::Color::Yellow, 'Y')); // No player assigned
                yellowCount--;
            } else if (redCount > 0) {
                setValueAt(x, y, Piece(x, y, nullptr, sf::Color::Red, 'R')); // No player assigned
                redCount--;
            } else if (blackCount > 0) {
                setValueAt(x, y, Piece(x, y, nullptr, sf::Color::Black, 'B')); // No player assigned
                blackCount--;
            }
        }
    }
}


void Board::movePiece(int x, int y, int newX, int newY)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols || newX < 0 || newX >= rows || newY < 0 || newY >= cols)
    {
        throw std::out_of_range("x or y is out of range");
    }

    setValueAt(newX, newY, *getValueAt(x, y));
    setValueAt(x, y, Piece(x, y, players[2], sf::Color::Transparent, ' '));
}

void Board::fillBoardWithEmptyPieces()
{
    std::cout << "inside fill board with empty pieces" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        std::cout<< "db1"  << std::endl;
        std::vector<std::unique_ptr<Piece>> row;
        for (int j = 0; j < cols; j++)
        {
            std::cout<< "db2"  << std::endl;
            row.push_back(std::make_unique<Piece>(i, j, nullptr, sf::Color::Transparent, ' '));
            std::cout<< "db3"  << std::endl;
        }
        std::cout<< "db4"  << std::endl;
        board.push_back(std::move(row));
        std::cout<< "db5"  << std::endl;

    }
}

// Checkers pour l'instant
void Board::setPiecesOnBoard()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i < 4 && (i + j) % 2 != 0)
            {
                setValueAt(i, j, Piece(i, j, players[0], sf::Color::Black, 'X'));
            }
            else if (i > 5 && (i + j) % 2 != 0)
            {
                setValueAt(i, j, Piece(i, j, players[1], sf::Color::White, 'O'));
            }
            else
                continue;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Board &board)
{
    for (int i = 0; i < board.getRows(); i++)
    {
        for (int j = 0; j < board.getCols(); j++)
        {
            os << *board.getValueAt(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

void Board::setDimensions(int newRows, int newCols)
{
    this->rows = newRows;
    this->cols = newCols;
}

Piece* Board::getValueAt(int x, int y) const
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        throw std::out_of_range("x or y is out of range");

    return board[x][y].get();
}

void Board::setValueAt(int x, int y, const Piece& piece)
{
    if (x < 0 || x >= rows || y < 0 || y >= cols)
    {
        throw std::out_of_range("x or y is out of range");
    }

    board[x][y] = std::make_unique<Piece>(piece);
}

int Board::getRows() const
{
    return rows;
}

int Board::getCols() const
{
    return cols;
}