/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** MissingFileException
*/

#include "MissingFileException.hpp"

Debug::MissingFileException::MissingFileException(const char *what, const char *where)
    : Exception(what, where)
{}
