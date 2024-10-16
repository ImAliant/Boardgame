#include "../Board.hpp"

using to_fill_t = std::vector<std::pair<char, int>>;

class ButinBoard: public Board
{
    private:
        void FillBoard() override;
        void ShuffleSymbols(std::vector<char>& symbols) const;
    public:
        explicit ButinBoard();
        ~ButinBoard() override = default;
};