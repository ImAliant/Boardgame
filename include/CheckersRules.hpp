#ifndef _CHECKERSRULES
#define _CHECKERSRULES

#include "Rules.hpp"

class CheckersRules: public Rules 
{
    public:
        bool isGameFinished() const override;
        ~CheckersRules() override = default;
};

#endif