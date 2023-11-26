#include "../../include/exception/GameTypeInvalidException.hpp"

GameTypeInvalidException::GameTypeInvalidException(const std::string &message): m_message(message) {}

const char *GameTypeInvalidException::what() const noexcept
{
    return m_message.c_str();
}