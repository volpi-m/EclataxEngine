/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ConfReader
*/

#include "ConfReader.hpp"

Client::ConfReader::ConfReader()
{
    readFile("ressources/.conf");
}

Client::ConfReader::ConfReader(const std::string &file)
{
    readFile(file);
}

Client::ConfReader::~ConfReader() {}

std::optional<std::string> Client::ConfReader::conf(const std::string &key) const
{
    if (_conf.count(key) > 0)
        return _conf.at(key);
    return {};
}

void Client::ConfReader::readFile(const std::string &file)
{
    std::ifstream ifs(file);

    if (!ifs)
        throw Debug::MissingFileException("configuration file not found",
            "Client::ConfReader::readFile");

    std::string line;
    while (std::getline(ifs, line)) {
        auto pos = line.find(":");
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.size());

        _conf.insert({key, value});
    }
    for (auto p : _conf)
        std::cout << p.first << " " << p.second << std::endl;
}
