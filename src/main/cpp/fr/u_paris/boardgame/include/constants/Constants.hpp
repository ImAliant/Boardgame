#pragma once

#include "../Types.hpp"

namespace Constants::Game
{
    namespace Checkers
    {
        const int BOARD_WIDTH{10};
        const int BOARD_HEIGHT{10};
        const int BLACK_PIECE_ROW{4};
        const int WHITE_PIECE_ROW{5};

        const char BLACK_PIECE_SYMBOL{'B'};
        const char WHITE_PIECE_SYMBOL{'W'};
    }
    namespace Butin
    {
        const int BOARD_WIDTH{8};
        const int BOARD_HEIGHT{8};

        const int RED_PIECE_NUMBER{20};
        const int YELLOW_PIECE_NUMBER{34};
        const int BLACK_PIECE_NUMBER{10};

        const char RED_PIECE_SYMBOL{'R'};
        const char YELLOW_PIECE_SYMBOL{'Y'};
        const char BLACK_PIECE_SYMBOL{'B'};
    }
    namespace Bulltricker
    {
        const int BOARD_WIDTH{15};
        const int BOARD_HEIGHT{15};

        /* const char BLACK_PIECE_SYMBOL{'B'};
        const char WHITE_PIECE_SYMBOL{'W'}; */
        const char BLACK_PAWN_SYMBOL{'P'};
        const char BLACK_QUEEN_SYMBOL{'Q'};
        const char BLACK_KING_SYMBOL{'K'};
        const char WHITE_PAWN_SYMBOL{'p'};
        const char WHITE_QUEEN_SYMBOL{'q'};
        const char WHITE_KING_SYMBOL{'k'};

        const int KING_TYPE{1};
        const int QUEEN_TYPE{2};
        const int PAWN_TYPE{3};

        const coord_t BLACK_KING_COORD{1, 7};
        const coord_t WHITE_KING_COORD{13, 7};
        const int BLACK_QUEEN_X{1};
        const int WHITE_QUEEN_X{13};

        const int BLACK_HORIZONTAL_PAWN_X{2};
        const int BLACK_VERTICAL_PAWN_X{3};
        const int WHITE_HORIZONTAL_PAWN_X{12};
        const int WHITE_VERTICAL_PAWN_X{11};
    }
}