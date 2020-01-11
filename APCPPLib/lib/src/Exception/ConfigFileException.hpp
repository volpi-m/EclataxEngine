/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ConfigFileException
*/

#ifndef CONFIGFILEEXCEPTION_HPP_
#define CONFIGFILEEXCEPTION_HPP_

#include "Exception.hpp"

namespace Debug
{
    class ConfigFileException : public Debug::Exception
    {
    public:
        ConfigFileException(const char *, const char *);
    };
}

#endif /* !CONFIGFILEEXCEPTION_HPP_ */
