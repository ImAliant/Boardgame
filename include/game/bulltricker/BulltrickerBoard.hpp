#pragma once 

#include "../../Piece.hpp"
#include "BulltrickerPiece.hpp"
#include "../../Constants.hpp"

#include <vector>

class BulltrickerPiece;

class BulltrickerBoard: public Board
{   
    private:
        std::unique_ptr<Piece> CreatePiece(coord_t coord, char color) const override;
        std::unique_ptr<BulltrickerPiece> CreateBlackPiece(coord_t coord, bool king, bool queen) const;
        std::unique_ptr<BulltrickerPiece> CreateWhitePiece(coord_t coord, bool king, bool queen) const;
    public:
        explicit BulltrickerBoard(std::vector<std::shared_ptr<Player>> players);
        ~BulltrickerBoard() override = default;

        void FillBoard() override;

        bool IsOpponentPiece(coord_t srcCoord, coord_t dstCoord) const;
};