//
// Created by tabis on 09/10/2019.
//

#pragma once

#include "macro.hpp"

#include <exception>
#include <iostream>

namespace Debug {
    class Exception : public std::exception {
    public:
        Exception() = default;
        Exception(const std::string &what, const std::string &where);
        Exception(const char *what, const char *where);
        ~Exception() override;

        void debugErrorMessage() const;

    private:
        std::string _what;
        std::string _where;
    };
}