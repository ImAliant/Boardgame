#include "../Board.hpp"

class CheckersBoard: public Board
{
    private:
        void FillBoard() override;
        void CreateBlackPiece(const int i, const int j);
        void CreateWhitePiece(const int i, const int j);
    public:
        explicit CheckersBoard();
        ~CheckersBoard() override = default;
};