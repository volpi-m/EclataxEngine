//
// EPITECH PROJECT, 2020
// R-type
// File description:
// class for lib loader
//

#include <iostream>
#include "DLLoader.hpp"

ECS::DLLoader::~DLLoader()
{
    for (auto &it : _ptr)
        dlclose(it);
    this->_ptr.clear();
}

void ECS::DLLoader::disp_error() const
{
    std::cout << dlerror() << std::endl;
}