#pragma once

#include "../View.hpp"
#include "../../game/bulltricker/BulltrickerPiece.hpp"

class BulltrickerView: public View
{   
    

    private:
        void SetupBoardPiece(const coord_t coord, const Board &board, const sf::Vector2f piecesize, const sf::Vector2f cellsize) override;
        void SetPieceTexture(sf::RectangleShape &piece, char color,bool promoted)override;
    public:
        BulltrickerView();
        ~BulltrickerView() override;

        void Init(std::shared_ptr<Context> context, const Board& board) override;

        void InitBoardCell(const Board& board) override;
        void InitDiffCellSize(const Board& board, const int rows, const int cols);

        void UpdateBoard(const Board& board) override;

        void SetPieceTexture(sf::RectangleShape &piece, const BulltrickerPiece &bulltrickerPiece,bool promoted);        

        void PrintCurrentPlayer(const std::shared_ptr<Player> currentPlayer) const override;
        void PrintWinner(const Player* winner) const override;


        sf::Vector2f GetPieceSize(const coord_t& coord, const Board& board) const;
        sf::Vector2f GetCellSize(const coord_t& coord, const Board& board) const;


        bool IsRoyalCell(const coord_t& coord) const;
        bool IsButéeCell(const coord_t& coord) const;
        bool IsHorizontalRectCell(const coord_t& coord) const;
        bool IsVerticalRectCell(const coord_t& coord) const;

        coord_t GetBoardCoord(const int x, const int y) const override;
};