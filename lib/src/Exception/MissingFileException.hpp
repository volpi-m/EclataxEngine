/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MissingFileException
*/

#ifndef MISSINGFILEEXCEPTION_HPP_
#define MISSINGFILEEXCEPTION_HPP_

#include "Exception.hpp"

namespace Debug
{
    class MissingFileException : public Debug::Exception
    {
    public:
        MissingFileException(const char *, const char *);
    };
}

#endif /* !MISSINGFILEEXCEPTION_HPP_ */
