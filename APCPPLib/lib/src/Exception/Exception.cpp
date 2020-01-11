//
// Created by tabis on 09/10/2019.
//

#include "Exception.hpp"

Debug::Exception::~Exception() = default;

void Debug::Exception::debugErrorMessage() const
{
    std::cerr << RED << "[Exception] " << MAGENTA << _what << WHITE << " in method " << BLUE << _where << std::endl;
}

Debug::Exception::Exception(const std::string &what, const std::string &where) : _what(what), _where(where) {}
Debug::Exception::Exception(const char *what, const char *where) : _what(what), _where(where) {}
