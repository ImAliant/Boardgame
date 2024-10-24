#pragma once

#include "Types.hpp"

class CoordUtils
{
    public:
        static coord_t CalculateNewCoord(const coord_t& coord, const dir_t& dir)
        {
            return {coord.first + dir.first, coord.second + dir.second};
        }
        static coord_t MultiplyCoord(const coord_t& coord, const int& factor)
        {
            return {coord.first * factor, coord.second * factor};
        }

        static std::vector<coord_t> GetNeighbours(const coord_t& coord, const int offset, const std::shared_ptr<Board> board)
        {
            std::vector<coord_t> neighbours;
            for (int i{-offset}; i <= offset; i++)
            {
                for (int j{-offset}; j <= offset; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }

                    const coord_t neighbour{coord.first + i, coord.second + j};
                    if (!board->IsInBoard(neighbour))
                    {
                        continue;
                    }

                    neighbours.push_back(neighbour);
                }
            }
            return neighbours;
        }
};