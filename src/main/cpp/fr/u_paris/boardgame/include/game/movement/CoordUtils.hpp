#pragma once

#include "Types.hpp"

class CoordUtils
{
    public:
        static coord_t CalculateNewCoord(const coord_t& coord, const dir_t& dir)
        {
            return {coord.first + dir.first, coord.second + dir.second};
        }
};