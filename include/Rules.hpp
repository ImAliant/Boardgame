#ifndef _RULES
#define _RULES

// Classe abstraite
class Rules
{
    public:
        virtual bool isGameFinished() const = 0;
        virtual ~Rules() = default;
};

#endif