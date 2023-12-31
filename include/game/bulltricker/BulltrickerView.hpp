#pragma once

#include "../View.hpp"

class BulltrickerView: public View
{
    private:
        void SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize) override;
        void SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted) override;
    public:
        BulltrickerView();
        ~BulltrickerView() override;

        void Init(std::shared_ptr<Context> context, const Board& board) override;

        void UpdateBoard(const Board& board) override;

        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const override;
        void PrintWinner(const Player* winner) const override;

        coord_t GetBoardCoord(const int x, const int y) const override;
};