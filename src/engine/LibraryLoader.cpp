//
// EPITECH PROJECT, 2020
// Module
// File description:
// class for lib loader
//

#include <iostream>
#include "LibraryLoader.hpp"

Module::LibraryLoader::~LibraryLoader()
{
    clear();
}

#if WIN32

void Module::LibraryLoader::clear()
{
    // Terminating all handlers.
    for (auto& it : _loadedLib)
        FreeLibrary((HMODULE)it.second);

    // Clearing the container.
    _loadedLib.clear();
}

#else

void Module::LibraryLoader::clear()
{
    for (auto &it : _loadedLib)
        dlclose(it.second);
    _loadedLib.clear();    
}

void *Module::LibraryLoader::loadLibrarie(const std::string &file)
{
    void *lib_ptr = nullptr;

    // Opening the dynamic library
    lib_ptr = dlopen(file.c_str(), RTLD_LAZY);

    // Checking if it has been loaded correctly.
    if (lib_ptr == nullptr)
    {
        return nullptr;
    }

    return lib_ptr;
}

#endif
