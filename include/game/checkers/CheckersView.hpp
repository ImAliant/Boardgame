#pragma once

#include "CheckersBoard.hpp"
#include "../View.hpp"

class CheckersView: public View
{
    private:
        void SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize) override;
        void SetPieceTexture(sf::RectangleShape &piece, const char color, const bool promoted) override;
    public:
        CheckersView();
        ~CheckersView() override;

        void Init(std::shared_ptr<Context> context, const CheckersBoard& board);

        void UpdateBoard(const CheckersBoard& board);

        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const override;
        void PrintWinner(const char winner) const;

        coord_t GetBoardCoord(const int x, const int y) const;
};