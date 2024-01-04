#pragma once 

#include "../../Piece.hpp"
#include "BulltrickerPiece.hpp"
#include "BulltrickerBoard.hpp"
#include "../../Constants.hpp"

#include <vector>

class BulltrickerPiece;

class BulltrickerBoard: public Board
{   
    private:
        std::unique_ptr<Piece> CreatePiece(coord_t coord, char color) const override;
        std::unique_ptr<BulltrickerPiece> CreateBlackPiece(coord_t coord, bool king, bool queen,bool isHorizontal) const;
        std::unique_ptr<BulltrickerPiece> CreateWhitePiece(coord_t coord, bool king, bool queen,bool isHorizontal) const;
    public:
        explicit BulltrickerBoard(std::vector<std::shared_ptr<Player>> players);
        ~BulltrickerBoard() override = default;

        friend std::ostream& operator<<(std::ostream& os, const BulltrickerBoard& board);

        void FillBoard() override;
       void ClearBoard();
       
        bool IsOpponentPiece(coord_t srcCoord, coord_t dstCoord) const;
        bool DetermineOrientation(int row, int col) const;
};