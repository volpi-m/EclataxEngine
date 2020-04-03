#ifndef LOG_HPP_
#define LOG_HPP_

#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

#if __linux__
    constexpr auto const RED = "\e[1;31m";
    constexpr auto const YELLOW = "\e[1;33m";
    constexpr auto const GREEN = "\e[1;32m";
    constexpr auto const BLUE = "\e[1;36m";
    constexpr auto const RESET = "\e[0m";
#elif _WIN32
    constexpr auto const RED = "";
    constexpr auto const YELLOW = "";
    constexpr auto const GREEN = "";
    constexpr auto const BLUE = "";
    constexpr auto const RESET = "";
#endif

namespace ECL
{
    /// \class Log
    /// \brief Small logger class using '<<' operator to log on std::cout or in a file
    class Log
    {
    public:
        /// \brief Deleted copy constructor
        Log(const Log &) = delete;

        /// \brief Deleted assignment operator
        Log &operator=(const Log &) = delete;

        ~Log() = default;

        /// \enum Priority
        /// \brief Enumeration with different priority level for logging messages.
        /// When a priority is set, all log with this priority and higher are logged
        enum Priority {
            Debug,
            Info,
            Warning,
            Error,
            None
        };

        /// \enum Control
        /// \brief Enumeration with different actions that can be done on the output
        /// like flush, print time, (de)activate colors etc.
        enum Control {
            Flush,
            Time,
            File,
            Cout,
            Color,
            UnColor
        };

        /// \brief Get the only instance of the logger (singleton)
        /// \return an instance of the logger
        static inline Log &get()
        {
            static Log instance("Log.txt");
            return instance;
        }

        /// \brief Overload of '<<' operator
        /// \param p : a value from the Priority enumeration
        /// \return a instance of the class to chain '<<' operation
        Log &operator<<(const Priority);

        /// \brief Overload of '<<' operator
        /// \param s : a string to output
        /// \return a instance of the class to chain '<<' operation
        Log &operator<<(const std::string &);

        /// \brief Overload of '<<' operator
        /// \param nb : any number to output to the screen
        /// \return a instance of the class to chain '<<' operation
        Log &operator<<(const double);

        /// \brief Overload of '<<' operator
        /// \param c : a value from the Control enumeration
        /// \return a instance of the class to chain '<<' operation
        Log &operator<<(const Control);

    private:
        /// \brief Private constructor
        /// \param file : path of the file to write log output
        Log(const std::string &);

        /// \brief Print time on the following format : [YYYY-MM-DD hh:mm:ss]
        void printTime();

        /// \brief Flush the output, add a new line and reset colors
        void flush();

        /// \brief Print the name of the output Priority given in '<<' operator
        /// \param desc : string describing the priotiry
        /// \param color : Priority will be written with the specified color
        void printDescription(const char *, const char *);

        /*! File stream */
        std::ofstream _f;
        /*! Minimum priority upon which messages will be printed */
        Priority _p;
        /*! Write color or not */
        bool _color;
        /*! Write in file or on std::cout */
        bool _inFile;
    };
}

#endif
