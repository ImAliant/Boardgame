#include "../../../include/game/butin/ButinBoard.hpp"
#include "../../../include/game/butin/Butin.hpp"

#include <random>
using namespace GameConstants::ButinConstants;

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
    std::fill_n(pieces.begin(), numYellow, BUTIN_YELLOW); 
    std::fill_n(pieces.begin() + numYellow, numRed, BUTIN_RED); 
    std::fill_n(pieces.begin() + numYellow + numRed, numBlack, BUTIN_BLACK); 

    // Shuffle 
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(pieces.begin(), pieces.end(), g);

    // Place the pieces 
    int pieceIndex = 0;
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            const auto& coord = std::make_pair(i, j);
            if (pieceIndex < totalPieces) {
                m_board[i][j] = CreatePiece(coord, pieces[pieceIndex]);
                pieceIndex++;
            } 
        }
    }

}
void ButinBoard::MovePiece(coord_t coord, coord_t newCoord)
{   
    CheckBounds(coord);
    CheckBounds(newCoord);

    // On recupere la piece a deplacer
    const auto& [x, y] = coord;
    auto piece = std::move(m_board[x][y]);
    piece->SetPosition(newCoord);

    const auto& [newX, newY] = newCoord;
    m_board[newX][newY] = std::move(piece);

    // TODO : remove jumped piece (a supprimer)
    RemoveJumpedPiece(coord, newCoord);
}

void ButinBoard::RemovePiece(coord_t coord)
{   
    CheckBounds(coord);

    const auto& [x, y] = coord;
    m_board[x][y] = nullptr;
}

bool ButinBoard::EmptyCell(coord_t coord) const
{
    CheckBounds(coord);

    return GetValueAt(coord) == nullptr;
}

//
void ButinBoard::RemoveJumpedPiece(coord_t start, coord_t end) {
    const auto& [startX, startY] = start;
    const auto& [endX, endY] = end;
    
    int jumpedX = (startX + endX) / 2;
    int jumpedY = (startY + endY) / 2;

    const auto& jumped = std::make_pair(jumpedX, jumpedY);
    RemovePiece(jumped); 
}
//

void ButinBoard::CheckBounds(coord_t coord) const
{
    const auto& [x, y] = coord;

    if (x < 0 || x >= m_rows || y < 0 || y >= m_cols)
    {
        throw std::out_of_range("x or y is out of range");
    }
}

bool ButinBoard::IsJumpablePiece(coord_t srcCoord, coord_t dstCoord) const
{
    CheckBounds(srcCoord);
    CheckBounds(dstCoord);

    //destination empty
    if (GetValueAt(dstCoord) != nullptr) return false;

    // Check if the start cell is a yellow piece 
    char startSymbol = GetValueAt(srcCoord)->GetSymbol();

    if (startSymbol != BUTIN_YELLOW) return false;

    return true;
}


std::unique_ptr<ButinPiece> ButinBoard::CreatePiece(coord_t coord, char color) const
{
    if (color == BUTIN_YELLOW)
        return CreateYellowPiece(coord);
    else if (color == BUTIN_RED)
        return CreateRedPiece(coord);
    else if (color == BUTIN_BLACK)
        return CreateBlackPiece(coord);
    else throw std::invalid_argument("Invalid color");
}

std::unique_ptr<ButinPiece> ButinBoard::CreateYellowPiece(coord_t coord) const {
    
    return std::make_unique<ButinPiece>(coord, BUTIN_YELLOW); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateRedPiece(coord_t coord) const {
    
    return std::make_unique<ButinPiece>(coord, BUTIN_RED); 
}

std::unique_ptr<ButinPiece> ButinBoard::CreateBlackPiece(coord_t coord) const {
    
    return std::make_unique<ButinPiece>(coord, BUTIN_BLACK); 
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