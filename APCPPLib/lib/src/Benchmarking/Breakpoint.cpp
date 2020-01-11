/*
 *
 *   Lucas Tabis
 *   Breakpoint class source file
 *
 *
 */

#include "Breakpoint.hpp"

Debug::Breakpoint::Breakpoint(const char *breakpointName, const char *breakpointWhere, char flags) : _start(std::chrono::high_resolution_clock::now()), _flags(flags), _name(breakpointName), _where(breakpointWhere) {}

Debug::Breakpoint::~Breakpoint()
{
    displayTimePassed();
}

void Debug::Breakpoint::displayTimePassed()
{
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    if (!(_flags & Flags::debug_off))
        std::cout << getCurrentTimeString(end) << "Breakpoint [" << REDUNDERLINED << "*" << WHITE << "]" <<
                     " Operation " << CYAN << _name << WHITE << " in " << MAGENTA << _where << WHITE <<
                     " lasted for " << std::chrono::duration_cast<std::chrono::microseconds>(end - _start).count() << " µs" << std::endl;
}

std::string Debug::Breakpoint::getCurrentTimeString(std::chrono::high_resolution_clock::time_point &end)
{
    std::ostringstream oss;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    oss << std::put_time(&tm, "(%Hh %Mm %Ss");
    oss << " " << std::to_string((std::chrono::duration_cast<std::chrono::milliseconds>(end.time_since_epoch()) % 1000).count()) << "ms";
    return BLUE + oss.str() + ") " + WHITE;
}