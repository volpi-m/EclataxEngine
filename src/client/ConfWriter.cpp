/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** ConfReader
*/

#include "ConfWriter.hpp"

Client::ConfWriter::ConfWriter(std::unordered_map<std::string, std::string> &conf, const std::string &file)
{
    writeFile(conf, file);
}

Client::ConfWriter::~ConfWriter() {}

void Client::ConfWriter::writeFile(std::unordered_map<std::string, std::string> &conf, const std::string &file)
{
    std::ofstream ofs(file, std::ofstream::out | std::ofstream::app); 

    // File could not be opened
    if (!ofs.is_open()) {
        Debug::Logger *log = Debug::Logger::getInstance(Debug::STANDARD);
            
        log->generateDebugMessage(Debug::WARNING, "Could not open file",
        "Client::ConfReader::writeFile");
        return;
    }

    // Writing configuration in current file
    for (auto &it : conf)
        ofs << it.first << ":" << it.second << std::endl;
    ofs.close();
}