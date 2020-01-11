/*
** EPITECH PROJECT, 2019
** libraryLoader.hpp
** File description:
** libraryLoader class
*/

#include "LibraryLoader.hpp"

void Utils::LibraryLoader::deleteHandles()
{
    for (auto &it : _handles)
        dlclose(it);
    _handles.clear();
}