#include "../../include/FontNotFoundException.hpp"

FontNotFoundException::FontNotFoundException(const std::string& errorMessage) : 
    errorMessage(errorMessage) {}

const char* FontNotFoundException::what() const noexcept {
    return errorMessage.c_str();
}