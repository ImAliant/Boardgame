#ifndef _FONTNOTFOUNDEXCEPTION
#define _FONTNOTFOUNDEXCEPTION

#include <exception>
#include <string>

class FontNotFoundException : public std::exception
{
    public:
        explicit FontNotFoundException(const std::string& errorMessage);
        const char* what() const noexcept override;
    private:
        std::string errorMessage;
};

#endif