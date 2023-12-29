#include "../../../include/game/checkers/CheckersView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace GameConstants;
using namespace CheckersConstants;
using namespace UIConstants;

CheckersView::CheckersView() {}

CheckersView::~CheckersView() {}

void CheckersView::Init(std::shared_ptr<Context> context, const CheckersBoard& board)
{
    const std::vector<int> textureIDs = {
        CHECKERS_BLACK_PAWN,
        CHECKERS_WHITE_PAWN,
        CHECKERS_BLACK_QUEEN,
        CHECKERS_WHITE_QUEEN,
        EMPTY_ASSET
    };

    InitBase(context, board, textureIDs, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void CheckersView::UpdateBoard(const CheckersBoard& board)
{
    UpdateBoardBase(board, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void CheckersView::SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    View::SetupBoardPiece(coord, board, piecesize, cellsize);

    const auto piece = dynamic_cast<const CheckersBoard&>(board).GetValueAt(coord);

    if (piece != nullptr)
        SetPieceTexture(m_boardPiece[coord.first][coord.second], piece->GetSymbol(), piece->IsPromoted());
    else SetPieceTexture(m_boardPiece[coord.first][coord.second], EMPTY_ID, false);
}

void CheckersView::SetPieceTexture(sf::RectangleShape &piece, char color, bool promoted)
{
    if (color == BLACK)
        piece.setTexture(promoted ? &m_pieceTexture[BLACKQUEEN_ID] : &m_pieceTexture[BLACKPAWN_ID]);
    else if (color == WHITE)
        piece.setTexture(promoted ? &m_pieceTexture[WHITEQUEEN_ID] : &m_pieceTexture[WHITEPAWN_ID]);
    else piece.setTexture(&m_pieceTexture[EMPTY_ID]);
}

void CheckersView::PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const
{
    system("clear");
    std::cout << "Current player: " << currentPlayer->ToString() << std::endl;
}
void CheckersView::PrintWinner(const char winner) const
{
    system("clear");
    std::string winnerStr;
    if (winner == WHITE) winnerStr = "White";
    else if (winner == BLACK) winnerStr = "Black";
    else winnerStr = "No winner";
    
    std::cout << "Winner: " << winnerStr << std::endl;
}

coord_t CheckersView::GetBoardCoord(const int x, const int y) const 
{
    return GetBoardCoordBase(x, y, BOARDCELL_SIZE);
}