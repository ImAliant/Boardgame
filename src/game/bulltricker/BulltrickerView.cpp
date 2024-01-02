#include "../../../include/game/bulltricker/BulltrickerView.hpp"

BulltrickerView::BulltrickerView() {}
BulltrickerView::~BulltrickerView() {}

using namespace GameConstants;
using namespace BulltrickerConstants;
using namespace UIConstants;

void BulltrickerView::Init(std::shared_ptr<Context> context, const Board& board)
{
    
    const std::vector<int> textureIDs = {
        BULLTRICKER_BLACK_PAWN,
        BULLTRICKER_WHITE_PAWN,
        BULLTRICKER_BLACK_QUEEN,
        BULLTRICKER_WHITE_QUEEN,
        BULLTRICKER_BLACK_KING,
        BULLTRICKER_WHITE_KING,
        EMPTY_ASSET
    };
//const sf::Vector2f DEFAULT_CELL_SIZE = sf::Vector2f(40.f, 40.f);  // Example size
//const sf::Vector2f DEFAULT_PIECE_SIZE = sf::Vector2f(36.f, 36.f); // Example size, slightly smaller than cell
   
    InitBase(context, board, textureIDs, ROYAL_BOARDPIECE_SIZE, ROYAL_CELL_SIZE);
}


void BulltrickerView::InitBoardCell(const Board& board)
    {
        View::InitBoardCell(board);

        InitDiffCellSize(board, board.GetRows(), board.GetCols());
    }

void BulltrickerView::InitDiffCellSize(const Board& board, const int rows, const int cols)
{
    const float offset = 10.f; // This offset is the padding around the entire board

    // Starting position for the first cell
    float currentX = offset;
    float currentY = offset;

    for (int i = 0; i < rows; i++) {
        currentX = offset; // Reset currentX to the starting X position for each new row

        for (int j = 0; j < cols; j++) {
            sf::Vector2f cellSize;

            // For even rows: butée cell, horizontal alley, butée cell, horizontal alley, ...
            // For odd rows: vertical alley, royal cell, vertical alley, royal cell, ...
            if (i % 2 == 0) {
                // Even row: Alternate between butée and horizontal alley cells
                cellSize = (j % 2 == 0) ? GameConstants::BulltrickerConstants::BUTEE_CELL_SIZE
                                        : GameConstants::BulltrickerConstants::HORIZONTAL_RECT_CELL_SIZE;
            } else {
                // Odd row: Alternate between vertical alley and royal cells
                cellSize = (j % 2 == 0) ? GameConstants::BulltrickerConstants::VERTICAL_RECT_CELL_SIZE
                                        : GameConstants::BulltrickerConstants::ROYAL_CELL_SIZE;
            }

            // Calculate the position of the current cell
            sf::Vector2f position(currentX, currentY);

            // Initialize the cell shape with the determined size and calculated position
            InitRectangleShape(
                m_boardCell[i][j],
                cellSize,
                position
            );

            // Set the color of the cell
            if ((i + j) % 2 == 0) {
                m_boardCell[i][j].setFillColor(GameConstants::BLACKCELL_COLOR);
            } else {
                m_boardCell[i][j].setFillColor(GameConstants::WHITECELL_COLOR);
            }

            // Increment currentX by the width of the current cell for the next cell in the same row
            currentX += cellSize.x;
        }

        // Increment currentY by the height of the first cell type in the row for the next row
        currentY += (i % 2 == 0) ? GameConstants::BulltrickerConstants::BUTEE_CELL_SIZE.y
                                 : GameConstants::BulltrickerConstants::VERTICAL_RECT_CELL_SIZE.y;
    }
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
    return std::make_pair(0, 0);
}