#include "../../../include/game/bulltricker/BulltrickerView.hpp"

BulltrickerView::BulltrickerView() {}
BulltrickerView::~BulltrickerView() {}

using namespace GameConstants;
using namespace BulltrickerConstants;
using namespace UIConstants;

void BulltrickerView::Init(std::shared_ptr<Context> context, const Board& board)
{
    // TODO
}

void BulltrickerView::UpdateBoard(const Board& board)
{
    // TODO
}

void BulltrickerView::SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize)
{
    // TODO
}

void BulltrickerView::SetPieceTexture(sf::RectangleShape &piece, char color, bool promoted)
{
    // TODO
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
    // TODO
}