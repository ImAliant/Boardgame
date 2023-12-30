#include "../../../include/game/butin/ButinView.hpp"
#include "../../../include/exception/AssetNotFoundException.hpp"

using namespace GameConstants::ButinConstants;
using namespace UIConstants;

ButinView::ButinView() {}

ButinView::~ButinView() {}

void ButinView::Init(std::shared_ptr<Context> context, const Board& board)
{
    const std::vector<int> textureIDs = {
        BUTIN_YELLOW_PIECE,
        BUTIN_RED_PIECE,
        BUTIN_BLACK_PIECE,
        EMPTY_ASSET
    };

    InitBase(context, board, textureIDs, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void ButinView::UpdateBoard(const Board& board)
{
    UpdateBoardBase(board, BOARDPIECE_SIZE, BOARDCELL_SIZE);
}

void ButinView::SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    View::SetupBoardPiece(coord, board, piecesize, cellsize);

    const auto piece = dynamic_cast<const ButinBoard&>(board).GetPiece(coord);

    if (piece != nullptr)
        SetPieceTexture(m_boardPiece[coord.first][coord.second], piece->GetSymbol(), false);
    else SetPieceTexture(m_boardPiece[coord.first][coord.second], EMPTY_ID, false);
}

void ButinView::SetPieceTexture(sf::RectangleShape &piece, char color, bool promoted)
{
    if (color == BUTIN_YELLOW)
        piece.setTexture(&m_pieceTexture[YELLOW_PAWN_ID]);
    else if (color == BUTIN_RED)
        piece.setTexture(&m_pieceTexture[RED_PAWN_ID]);
    else if (color == BUTIN_BLACK)
        piece.setTexture(&m_pieceTexture[BLACK_PAWN_ID]);
    else piece.setTexture(&m_pieceTexture[EMPTY_ID]);
}

void ButinView::PrintTurn(const std::shared_ptr<Player> currentPlayer, const std::vector<std::shared_ptr<Player>>& players) const
{
    system("clear");
    PrintCurrentPlayer(currentPlayer);
    PrintPlayersScore(players);
}
void ButinView::PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const
{
    system("clear");
    if (currentPlayer->GetId()%2 == GameConstants::PLAYER_ONEID) 
        std::cout << "Current player: " << GameConstants::PLAYER_ONEID << std::endl;
    else std::cout << "Current player: " << GameConstants::PLAYER_TWOID << std::endl;
}
void ButinView::PrintPlayersScore(const std::vector<std::shared_ptr<Player>>& players) const
{
    for (const auto& player : players) {
        PrintScore(player->GetScore());
    }
}
void ButinView::PrintWinner(const Player* winner) const
{
    system("clear");
    if (winner)
    {
        if (winner->GetId()%2 == GameConstants::PLAYER_ONEID) 
            std::cout << "The winner is: " << GameConstants::PLAYER_ONEID << std::endl;
        else std::cout << "The winner is: " << GameConstants::PLAYER_TWOID << std::endl;
    }
    else std::cout << "No winner determined." << std::endl;
}
void ButinView::PrintScore(int score) const{
    std::cout << "Score: " << score << std::endl;
}

coord_t ButinView::GetBoardCoord(const int x, const int y) const 
{
    return GetBoardCoordBase(x, y, BOARDCELL_SIZE);
}
