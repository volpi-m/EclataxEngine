//
// Created by tabis on 09/10/2019.
//

#pragma once

#define RED             "\033[0;31m"
#define REDUNDERLINED   "\033[0;41m"
#define GREEN           "\033[0;32m"
#define YELLOW          "\033[0;33m"
#define BLUE            "\033[0;34m"
#define MAGENTA         "\033[0;35m"
#define CYAN            "\033[0;36m"
#define WHITE           "\033[m"

#define DEFAULT_LOG_FILE    "output.txt"
#define WARNING_MESSAGE     "[Warning]"
#define ERROR_MESSAGE       "[Error]"
#define DEBUG_MESSAGE       "[Debug]"
#define FATAL_MESSAGE       "[FATAL]"
#define INFO_MESSAGE        "[Info]"
#define BREAKPOINT_MESSAGE  "[" REDUNDERLINED "0" WHITE "][Breakpoint]"

// Flags options for the Logger class
namespace Debug {
    namespace Flags {
        typedef enum e_options {all_on = 1, debug_off = 2, info_off = 4, warning_off = 8, error_off = 16, fatal_off = 32} options;
    }
}
