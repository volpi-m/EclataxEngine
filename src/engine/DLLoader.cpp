//
// EPITECH PROJECT, 2020
// R-type
// File description:
// class for lib loader
//

#include <iostream>
#include "DLLoader.hpp"

ECS::DLLoader::DLLoader()
{ }

ECS::DLLoader::~DLLoader()
{
    for (std::vector<void *>::iterator i = this->_ptr.begin(); i != this->_ptr.end(); i++) {
        dlclose(*i);
    }
    this->_ptr.clear();
}

void ECS::DLLoader::disp_error() const
{
    std::cout << dlerror() << std::endl;
}