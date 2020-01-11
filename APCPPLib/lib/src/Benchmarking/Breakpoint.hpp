/*
 *
 *   Lucas Tabis
 *   Breakpoint class source file
 *
 *
 */

#include <iomanip>
#include <sstream>
#include <iostream>
#include <chrono>
#include <mutex>

#include "macro.hpp"

namespace Debug {

    class Breakpoint {
        public:
            Breakpoint(const char *breakpointName, const char *breakpointWhere, char flags = Flags::all_on);
            ~Breakpoint();

        private:
            void displayTimePassed();
            std::string getCurrentTimeString(std::chrono::high_resolution_clock::time_point &end);
            std::chrono::high_resolution_clock::time_point _start;
            char _flags;
            const char *_name;
            const char *_where;
            std::mutex _mutex;
    };
}