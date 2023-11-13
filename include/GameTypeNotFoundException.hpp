#ifndef _GAMETYPENOTFOUNDEXCEPTION
#define _GAMETYPENOTFOUNDEXCEPTION

#include <exception>
#include <string>

class GameTypeNotFoundException : public std::exception
{
    public:
        explicit GameTypeNotFoundException(const std::string& errorMessage);
        const char* what() const noexcept override;
    private:
        std::string errorMessage;
};

#endif