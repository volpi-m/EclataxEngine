/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** TcpSocketException
*/

#ifndef TCPSOCKETEXCEPTION_HPP_
#define TCPSOCKETEXCEPTION_HPP_

#include "Exception.hpp"

namespace Debug
{
    class TcpSocketException : public Debug::Exception
    {
    public:
        TcpSocketException(const char *, const char *);
    };
}

#endif /* !TCPSOCKETEXCEPTION_HPP_ */
