#include "../../include/GameTypeNotFoundException.hpp"

GameTypeNotFoundException::GameTypeNotFoundException(const std::string& errorMessage) : 
    errorMessage(errorMessage) {}

const char* GameTypeNotFoundException::what() const noexcept 
{
    return errorMessage.c_str();
}