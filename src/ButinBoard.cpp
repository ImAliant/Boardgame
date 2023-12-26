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
    const int numYellow = 34;
    const int numRed = 20;
    const int numBlack = 10;
    const int totalPieces = numYellow + numRed + numBlack;

    std::vector<char> pieces(totalPieces);
    std::fill_n(pieces.begin(), numYellow, 'Y'); 
    std::fill_n(pieces.begin() + numYellow, numRed, 'R'); 
    std::fill_n(pieces.begin() + numYellow + numRed, numBlack, 'B'); 

    // Shuffle 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pieces.begin(), pieces.end(), g);

    // Place the pieces 
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

    RemovePiece(jumpedX,jumpedY); 
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

    char startSymbol = GetValueAt(sx, sy)->GetSymbol();
    char destSymbol = GetValueAt(dx, dy)->GetSymbol();

    //destination empty
    if (destSymbol == 'T') { 
        return false;
    }

    // Check if the start cell is a yellow piece 
    if (startSymbol != 'Y') { 
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
    
    return std::make_unique<ButinPiece>(x, y, 'Y'); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateRedPiece(int x, int y) const {
    
    return std::make_unique<ButinPiece>(x, y,'R'); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateBlackPiece(int x, int y) const {
    
    return std::make_unique<ButinPiece>(x, y, 'B'); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateTransparentPiece(int x, int y) const {
    
    return std::make_unique<ButinPiece>(x, y, 'T'); 
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