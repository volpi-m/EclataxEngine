/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ConfReader
*/

/// \file ConfReader.hpp
/// \author Matteo V.
/// \brief Header file to read configuration file

#ifndef CONFREADER_HPP_
#define CONFREADER_HPP_

#include <unordered_map>
#include <optional>
#include <string>
#include <fstream>
#include <iostream>
#include "MissingFileException.hpp"

/// \namespace Common
/// \brief Used for ressources common to server and client
namespace Common
{
    /// \class ConfReader
    /// \brief Read values from a configuration file and store it in a map
    class ConfReader
    {
    public:
        /// \brief Constructor
        /// read configuration in a file located in 'ressources/.conf'
        ConfReader();

        /// \brief Constructor
        /// read configuration in a specified file
        /// \param file : configuration file to read
        ConfReader(const std::string &);

        /// \brief Destructor
        ~ConfReader();

        /// \param key : name of the parameter you want to get from the configuration file
        /// \return a std::optional containing a value if the specified key was valid
        /// \brief Return the value associated to a key
        std::optional<std::string> conf(const std::string &) const;

    private:
        /// \param 
        void readFile(const std::string &);

        /*! map containing each key and value read from the configuration file */
        std::unordered_map<std::string, std::string> _conf;
    };
}

#endif /* !CONFREADER_HPP_ */
