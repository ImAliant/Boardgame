#pragma once

#include "../ModelFlags.hpp"

class BulltrickerFlags: public ModelFlags
{
    public:
        BulltrickerFlags() = default;
        ~BulltrickerFlags() override = default;

        void ResetFlags() override {};
};