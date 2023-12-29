#pragma once

#include "ButinBoard.hpp"
#include "../View.hpp"

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class ButinView: public View
{
    private:
        void SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize) override;
        void SetPieceTexture(sf::RectangleShape &piece, char color, bool promoted) override;
    public:
        ButinView();
        ~ButinView() override;

        void Init(std::shared_ptr<Context> context, const ButinBoard& board);

        void UpdateBoard(const ButinBoard& board);

        void PrintTurn(const std::shared_ptr<Player> currentPlayer, const std::vector<std::shared_ptr<Player>>& players) const;
        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const override;
        void PrintPlayersScore(const std::vector<std::shared_ptr<Player>>& players) const;
        void PrintScore(const int score) const;
        void PrintWinner(const Player* winner) const;

        coord_t GetBoardCoord(int x, int y) const;
};