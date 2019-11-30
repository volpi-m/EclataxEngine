/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ConfWriter
*/

/// \file ConfWriter.hpp
/// \author Lucas T.
/// \brief Header file to write in configuration files

#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "MissingFileException.hpp"
#include "Logger.hpp"

namespace Common
{
    /// \class ConfWriter
    /// \brief Write a given configuration in a configuration file
    class ConfWriter {
    public:
        /// \brief Constructor
        /// write configuration in a specified file
        /// \param file : configuration file to read
        ConfWriter(std::unordered_map<std::string, std::string> &conf, const std::string &file);

        /// \brief Destructor
        ~ConfWriter();

    private:

        /// \brief write a config in a file
        /// \param conf : data to be written
        /// \param file : configuration file to read
        void writeFile(std::unordered_map<std::string, std::string> &conf, const std::string &file);
    };
}