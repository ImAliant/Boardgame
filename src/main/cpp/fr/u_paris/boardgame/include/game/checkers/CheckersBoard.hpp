#include "../Board.hpp"

class CheckersBoard: public Board
{
    private:
        void FillBoard() override;
    public:
        explicit CheckersBoard();
        ~CheckersBoard() override = default;
};