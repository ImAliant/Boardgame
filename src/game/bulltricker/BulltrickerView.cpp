#include "../../../include/game/bulltricker/BulltrickerView.hpp"
#include "../../../include/game/bulltricker/BulltrickerBoard.hpp"

BulltrickerView::BulltrickerView() {}
BulltrickerView::~BulltrickerView() {}

using namespace GameConstants;
using namespace BulltrickerConstants;
using namespace UIConstants;

void BulltrickerView::Init(std::shared_ptr<Context> context, const Board& board)
{
    
    const std::vector<int> textureIDs = {
        BULLTRICKER_BLACK_HORIZ_PAWN,
        BULLTRICKER_WHITE_HORIZ_PAWN,
        BULLTRICKER_BLACK_VERT_PAWN,
        BULLTRICKER_WHITE_VERT_PAWN,
        BULLTRICKER_BLACK_HORIZ_QUEEN,
        BULLTRICKER_WHITE_HORIZ_QUEEN,
        BULLTRICKER_BLACK_VERT_QUEEN,
        BULLTRICKER_WHITE_VERT_QUEEN,
        BULLTRICKER_BLACK_KING,
        BULLTRICKER_WHITE_KING,
        EMPTY_ASSET
    };

   
    InitBase(context, board, textureIDs, ROYAL_BOARDPIECE_SIZE, ROYAL_CELL_SIZE);
}


void BulltrickerView::InitBoardCell(const Board& board)
    {
        View::InitBoardCell(board);

        InitDiffCellSize(board, board.GetRows(), board.GetCols());
    }

void BulltrickerView::InitDiffCellSize(const Board& board, const int rows, const int cols)
{
    const float offset = 10.f; 
    // Starting position for the first cell
    float currentX = offset;
    float currentY = offset;

    for (int i = 0; i < rows; i++) {
        currentX = offset; 
        for (int j = 0; j < cols; j++) {
            sf::Vector2f cellSize;
            if (i % 2 == 0) { 
                cellSize = (j % 2 == 0) ? GameConstants::BulltrickerConstants::BUTEE_CELL_SIZE
                                        : GameConstants::BulltrickerConstants::HORIZONTAL_RECT_CELL_SIZE;
            }else {                
                cellSize = (j % 2 == 0) ? GameConstants::BulltrickerConstants::VERTICAL_RECT_CELL_SIZE
                                        : GameConstants::BulltrickerConstants::ROYAL_CELL_SIZE;
                }
            sf::Vector2f position(currentX, currentY);

            InitRectangleShape(
                m_boardCell[i][j],
                cellSize,
                position
            );

            if ((i + j) % 2 == 0) {
                m_boardCell[i][j].setFillColor(GameConstants::BLACKCELL_COLOR);
            } else {
                m_boardCell[i][j].setFillColor(GameConstants::WHITECELL_COLOR);
            }
            currentX += cellSize.x;
        }
        currentY += (i % 2 == 0) ? GameConstants::BulltrickerConstants::BUTEE_CELL_SIZE.y
                                 : GameConstants::BulltrickerConstants::VERTICAL_RECT_CELL_SIZE.y;
    }
}


void BulltrickerView::UpdateBoard(const Board& board)
{
    UpdateBoardBase(board, ROYAL_BOARDPIECE_SIZE, ROYAL_CELL_SIZE);
}

void BulltrickerView::SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    sf::Vector2f Real_piecesize = GetPieceSize(coord, board);
    sf::Vector2f Real_cellsize = GetCellSize(coord, board);
    View::SetupBoardPiece(coord, board, Real_piecesize, Real_cellsize);

    const auto piece = dynamic_cast<const BulltrickerBoard&>(board).GetPiece(coord);
    const auto bulltrickerPiece = dynamic_cast<const BulltrickerPiece*>(piece); 

    if (bulltrickerPiece != nullptr) {
        SetPieceTexture(m_boardPiece[coord.first][coord.second], *bulltrickerPiece, bulltrickerPiece->IsPromoted());
    } else {
        SetPieceTexture(m_boardPiece[coord.first][coord.second], EMPTY_ID, false);
    }
}


void BulltrickerView::SetPieceTexture(sf::RectangleShape &piece, char color, bool promoted) {
   
}
void BulltrickerView::SetPieceTexture(sf::RectangleShape &piece, const BulltrickerPiece &bulltrickerPiece,bool promoted)
{   
    switch (bulltrickerPiece.GetType()) {
       
        case BullT_PieceType::BT_PAWN:
            if (bulltrickerPiece.GetSymbol() == GameConstants::BulltrickerConstants::BLACK) {
               
                if(!promoted)
                    piece.setTexture(bulltrickerPiece.IsHorizontal() ? &m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_HORIZ_PAWN_ID]
                                                                 : &m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_VERT_PAWN_ID]);
                else 
                piece.setTexture(bulltrickerPiece.IsHorizontal() ? &m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_HORIZ_QUEEN_ID]
                                                                 : &m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_VERT_QUEEN_ID]);
            } else if (bulltrickerPiece.GetSymbol() == GameConstants::BulltrickerConstants::WHITE) 
                piece.setTexture(bulltrickerPiece.IsHorizontal() ? &m_pieceTexture[GameConstants::BulltrickerConstants::WHITE_HORIZ_PAWN_ID]
                                                                 : &m_pieceTexture[GameConstants::BulltrickerConstants::WHITE_VERT_PAWN_ID]);
            
            break;
        case BullT_PieceType::BT_QUEEN:
            if (bulltrickerPiece.GetSymbol() == GameConstants::BulltrickerConstants::BLACK) {
                piece.setTexture(bulltrickerPiece.IsHorizontal() ? &m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_HORIZ_QUEEN_ID]
                                                                 : &m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_VERT_QUEEN_ID]);
            } else if (bulltrickerPiece.GetSymbol() == GameConstants::BulltrickerConstants::WHITE) {
                piece.setTexture(bulltrickerPiece.IsHorizontal() ? &m_pieceTexture[GameConstants::BulltrickerConstants::WHITE_HORIZ_QUEEN_ID]
                                                                 : &m_pieceTexture[GameConstants::BulltrickerConstants::WHITE_VERT_QUEEN_ID]);
            }
            break;
        case BullT_PieceType::KING:
            if (bulltrickerPiece.GetSymbol() == GameConstants::BulltrickerConstants::BLACK) {
                piece.setTexture(&m_pieceTexture[GameConstants::BulltrickerConstants::BLACK_KING_ID]);
            } else if (bulltrickerPiece.GetSymbol() == GameConstants::BulltrickerConstants::WHITE) {
                piece.setTexture(&m_pieceTexture[GameConstants::BulltrickerConstants::WHITE_KING_ID]);
            }
            break;
        default:
            piece.setTexture(&m_pieceTexture[GameConstants::BulltrickerConstants::EMPTY_ID]);
            break;
    }
}

void BulltrickerView::PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const
{
    system("clear");
    if (currentPlayer->GetId()%2 == PLAYER_ONEID) std::cout << "Current player: White" << std::endl;
    else std::cout << "Current player: Black" << std::endl;
}

void BulltrickerView::PrintWinner(const Player* winner) const
{
    system("clear");
    std::string winnerStr;
    if (winner)
    {
        if (winner->GetId()%2 == PLAYER_ONEID) winnerStr = "White";
        else winnerStr = "Black";
        std::cout << "Winner: " << winnerStr << std::endl;
    }
    else std::cout << "Draw" << std::endl;
}

coord_t BulltrickerView::GetBoardCoord(const int x, const int y) const
{
    return GetBoardCoordBase(x, y, ROYAL_CELL_SIZE);
}


sf::Vector2f BulltrickerView::GetPieceSize(const coord_t& coord, const Board& board) const {
   
    if (IsRoyalCell(coord)) {
        return GameConstants::BulltrickerConstants::ROYAL_BOARDPIECE_SIZE;
    } else if (IsHorizontalRectCell(coord)) {
        return GameConstants::BulltrickerConstants::HORIZONTAL_RECT_BOARDPIECE_SIZE;
    } else if (IsVerticalRectCell(coord)) {
        return GameConstants::BulltrickerConstants::VERTICAL_RECT_BOARDPIECE_SIZE;
    } 
    return sf::Vector2f(-1, -1);
}

sf::Vector2f BulltrickerView::GetCellSize(const coord_t& coord, const Board& board) const {
 
    if (IsButéeCell(coord)) {
        return GameConstants::BulltrickerConstants::BUTEE_CELL_SIZE;
    } else if (IsRoyalCell(coord)) {
        return GameConstants::BulltrickerConstants::ROYAL_CELL_SIZE;
    } else if (IsHorizontalRectCell(coord)) {
        return GameConstants::BulltrickerConstants::HORIZONTAL_RECT_CELL_SIZE;
    } else if (IsVerticalRectCell(coord)) {
        return GameConstants::BulltrickerConstants::VERTICAL_RECT_CELL_SIZE;
    } 
    return sf::Vector2f(-1, -1);
}

bool BulltrickerView::IsButéeCell(const coord_t& coord) const {
    
    return (coord.first % 2 == 0) && (coord.second % 2 == 0);
}

bool BulltrickerView::IsRoyalCell(const coord_t& coord) const {
    
    return (coord.first % 2 != 0) && (coord.second % 2 != 0);
}

bool BulltrickerView::IsHorizontalRectCell(const coord_t& coord) const {
    
    return (coord.first % 2 == 0) && (coord.second % 2 != 0);
}

bool BulltrickerView::IsVerticalRectCell(const coord_t& coord) const {
   
    return (coord.first % 2 != 0) && (coord.second % 2 == 0);
}