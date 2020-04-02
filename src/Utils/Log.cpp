#include "Log.hpp"

ECL::Log::Log(const std::string &file) : _f(file), _p(Debug), _color(false), _inFile(false) {}

ECL::Log &ECL::Log::operator<<(Priority p)
{
    if (p == Debug)
        printDescription("Debug\t", GREEN);
    else if (p == Info)
        printDescription("Info\t", BLUE);
    else if (p == Warning)
        printDescription("Warning\t", YELLOW);
    else if (p == Error)
        printDescription("Error\t", RED);
    else
        printDescription("None\t", "");
    return *this;
}

ECL::Log &ECL::Log::operator<<(const std::string &s)
{
    if (_inFile)
        _f << s;
    else
        std::cout << s;
    return *this;
}

ECL::Log &ECL::Log::operator<<(const double nb)
{
    if (_inFile)
        _f << nb;
    else
        std::cout << nb;
    return *this;
}

ECL::Log &ECL::Log::operator<<(const Control c)
{
    if (c == Flush)
        flush();
    else if (c == Time)
        printTime();
    else if (c == File)
        _inFile = true;
    else if (c == Cout)
        _inFile = false;
    else if (c == Color)
        _color = true;
    else if (c == UnColor)
        _color = false;
    return *this;
}

void ECL::Log::printTime()
{
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);

    if (_inFile)
    {
        _f << "["
            << std::put_time(std::localtime(&t), "%F %T")
        << "] ";
    }
    else
    {
        std::cout << "["
            << std::put_time(std::localtime(&t), "%F %T")
        << "] ";
    }
}

void ECL::Log::flush()
{
    if (_inFile)
        _f << std::endl;
    else
        std::cout << RESET << std::endl;
}

void ECL::Log::printDescription(const char *desc, const char *color)
{
    if (_inFile)
        _f << desc;
    else
    {
        if (_color)
            std::cout << color;
        std::cout << desc;
    }
}
