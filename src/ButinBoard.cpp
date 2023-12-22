#include "../include/ButinBoard.hpp"
#include "../include/game/Butin/Butin.hpp"
#include <random>
using namespace ButinConstants;

ButinBoard::ButinBoard(std::vector<std::shared_ptr<Player>> players)
: Board(std::move(players))
{
    m_rows = BUTINROWS;
    m_cols = BUTINCOLS;

    ButinBoard::Init();
}



void ButinBoard::Init()
{
    m_board.resize(m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        m_board[i].resize(m_cols);
    }

    FillBoard();
}

void ButinBoard::FillBoard() 
{
// Assuming constants for the number of each type of piece
    const int numYellow = 34;
    const int numRed = 20;
    const int numBlack = 10;
    const int totalPieces = numYellow + numRed + numBlack;

    std::vector<char> pieces(totalPieces);
    std::fill_n(pieces.begin(), numYellow, 'Y'); // 'Y' for yellow
    std::fill_n(pieces.begin() + numYellow, numRed, 'R'); // 'R' for red
    std::fill_n(pieces.begin() + numYellow + numRed, numBlack, 'B'); // 'B' for black

    // Shuffle the pieces to randomize their placement
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pieces.begin(), pieces.end(), g);

    // Place the pieces on the board
    int pieceIndex = 0;
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (pieceIndex < totalPieces) {
                m_board[i][j] = CreatePiece(i, j, pieces[pieceIndex]);
                pieceIndex++;
            } 
        }
    }

}
void ButinBoard::MovePiece(int x, int y, int newX, int newY)
{
    
    CheckBounds(x, y);
    CheckBounds(newX, newY);

    // On recupere la piece a deplacer
    auto piece = std::move(m_board[x][y]);
    piece->SetPosition(newX, newY);

    m_board[newX][newY] = std::move(piece);
    m_board[x][y] = CreatePiece(x, y, TRANSPARENT);
    removeJumpedPiece(x, y, newX, newY);

}

void ButinBoard::RemovePiece(int x, int y)
{   CheckBounds(x, y);

    m_board[x][y] = CreatePiece(x, y, TRANSPARENT);
    
}
void ButinBoard::removeJumpedPiece(int startX, int startY, int endX, int endY) {
    int jumpedX = (startX + endX) / 2;
    int jumpedY = (startY + endY) / 2;

    // Assuming board is a 2D array representing the game board
    RemovePiece(jumpedX,jumpedY); // Set the cell to empty
     // Update the player's score (if needed
   
}



void ButinBoard::CheckBounds(int x, int y) const
{
    if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
    {
        throw std::out_of_range("x or y is out of range");
    }
}

bool ButinBoard::IsJumpablePiece(int sx, int sy, int dx, int dy) const
{
    CheckBounds(sx, sy);
    CheckBounds(dx, dy);

    // Assuming GetSymbol returns the color/type of the piece
    char startSymbol = GetValueAt(sx, sy)->GetSymbol();
    char destSymbol = GetValueAt(dx, dy)->GetSymbol();

    // Check if the destination cell is empty (i.e., a valid space to jump to)
    if (destSymbol == 'T') { // 'T' for transparent/empty
        return false;
    }

    // Check if the start cell is a yellow piece (the only movable piece in Butin)
    if (startSymbol != 'Y') { // 'Y' for yellow
        return false;
    }

    

    return true;
}


std::unique_ptr<ButinPiece> ButinBoard::CreatePiece(int x, int y, char color) const
{
    switch (color) {
        case 'Y':
            return CreateYellowPiece(x, y);
        case 'R':
            return CreateRedPiece(x, y);
        case 'B':
            return CreateBlackPiece(x, y);
        case 'T':
            return CreateTransparentPiece(x, y);
        default:
            throw std::invalid_argument("Invalid color");
    }
}

std::unique_ptr<ButinPiece> ButinBoard::CreateYellowPiece(int x, int y) const {
    // Logic to create a yellow Butin piece
    return std::make_unique<ButinPiece>(x, y, 'Y'); // Adjust constructor as needed
}

std::unique_ptr<ButinPiece> ButinBoard::CreateRedPiece(int x, int y) const {
    // Logic to create a red Butin piece
    return std::make_unique<ButinPiece>(x, y,'R'); // Adjust constructor as needed
}

std::unique_ptr<ButinPiece> ButinBoard::CreateBlackPiece(int x, int y) const {
    // Logic to create a black Butin piece
    return std::make_unique<ButinPiece>(x, y, 'B'); // Adjust constructor as needed
}

std::unique_ptr<ButinPiece> ButinBoard::CreateTransparentPiece(int x, int y) const {
    // Logic to create a transparent (empty) cell
    return std::make_unique<ButinPiece>(x, y, 'T'); // Adjust constructor as needed
}
bool ButinBoard::EmptyCell(int x, int y) const
{
    CheckBounds(x, y);

    return GetValueAt(x, y)->GetSymbol() == TRANSPARENT;
}


std::ostream &operator<<(std::ostream &os, const ButinBoard &board)
{
    for (int i = 0; i < board.m_rows; i++)
    {
        for (int j = 0; j < board.m_cols; j++)
        {
            os << *board.m_board[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}