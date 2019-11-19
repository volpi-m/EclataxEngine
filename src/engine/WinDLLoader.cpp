//
// EPITECH PROJECT, 2020
// R-type
// File description:
// class for lib loader
//

#include <iostream>
#include "winDLLoader.hpp"

ECS::WinDLLoader::DLLoader()
{ }

ECS::WinDLLoader::~DLLoader()
{
    for (std::vector<void *>::iterator i = this->_ptr.begin(); i != this->_ptr.end(); i++) {
        dlclose(*i);
    }
    this->_ptr.clear();
}

void ECS::WinDLLoader::disp_error() const
{
    std::cout << GetLastError() << std::endl;
}

