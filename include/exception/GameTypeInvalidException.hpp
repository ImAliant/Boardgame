#pragma once

#include <exception>
#include <string>

class GameTypeInvalidException: public std::exception
{
    private:
        std::string m_message;
    public:
        explicit GameTypeInvalidException(const std::string &message);
        const char *what() const throw() override;
};