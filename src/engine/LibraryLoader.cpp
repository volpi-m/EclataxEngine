//
// EPITECH PROJECT, 2020
// R-type
// File description:
// class for lib loader
//

#include "DLLoader.hpp"

ECL::LibraryLoader::~DLLoader()
{
    for (auto &it : _ptr)
        dlclose(it);
    this->_ptr.clear();
}

void ECL::LibraryLoader::disp_error() const
{
    std::cout << dlerror() << std::endl;
}