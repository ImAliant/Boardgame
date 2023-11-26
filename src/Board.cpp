#include <iostream>

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
            case GameType::JEU1:
                //setDimensions(?, ?);
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
    }
}

void Board::initCheckersBoard()
{
    // initialize the board with empty pieces
    fillBoardWithEmptyPieces();

    // Set the pieces on the board
    setPiecesOnBoard();
}

void Board::fillBoardWithEmptyPieces()
{
    for (int i = 0; i < rows; i++)
    {
        std::vector<std::unique_ptr<Piece>> row;
        for (int j = 0; j < cols; j++)
        {
            row.push_back(std::make_unique<Piece>(i, j, players[2], sf::Color::Transparent, ' '));
        }
        board.push_back(std::move(row));
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