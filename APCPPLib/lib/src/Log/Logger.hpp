/*
*
*   Lucas Tabis
*   Logger class source file
*
*
*/

#pragma once

#include <ratio>
#include <queue>
#include <mutex>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <condition_variable>

#include "macro.hpp"

/// \class Debug
namespace Debug
{

    /// \enum mode
    /// \brief output target.
    typedef enum e_mode {STANDARD, FILE, OFF} mode;

    /// \enum type
    /// \brief types of messages.
    typedef enum e_type {DEBUG = 2, INFO = 4, WARNING = 8, ERROR = 16, FATAL = 32} type;

    /// \class Logger
    /// \brief A static object that can send formated debug message to a file or the standard output.
    class Logger
    {
        public:
            /// \brief Illegal constructor.
            Logger(const Logger&) = delete;

            /// \brief Illegal = operator.
            Logger& operator=(const Logger&) = delete;

            /// \brief Dtor.
            ~Logger();
        
            /// \brief Print a formated message on the screen via a different thread.
            /// \param type : the type of the message.
            /// \param message : the message that we want to display.
            /// \param where : from where the debug as been executed.
            static void printDebug(type type, const std::string &message, const std::string &where = "unknown")
            {
                Logger *instance = getInstance();

                if (instance->_mode == STANDARD && !(instance->_flags & type))
                        instance->generateMessageOnStandardOutput(type, message, where);
                    else if (instance->_mode == FILE && !(instance->_flags & type))
                        instance->generateMessageInFile(type, message, where);
                    instance->_condVar.notify_one();
                    instance->_bNotified = true;
            }

            /// \brief Print a message on the screen via a different thread.
            /// \param formated : the already formated message.
            static void printDebug(const std::string &formated)
            {
                Logger *instance = getInstance();

                if (instance->_mode == STANDARD)
                    std::cout << formated << std::endl;
                else if (instance->_mode == FILE && instance->_file.is_open())
                    instance->_file << formated << std::endl;

            }

            /// \brief Tells the logger what message type it needs to display on screen.
            /// \param flags : flags of types.
            static void setFlags(char flags)
            {
                Logger *instance = getInstance();

                instance->_flags = flags;
            }

            /// \brief Changes the logger mode, to file writing or standard output writing.
            /// \param flags : mode to set.
            static void switchMode(mode mode)
            {
                Logger *instance = getInstance();

                instance->_mode = mode;

                if (mode != FILE && instance->_file.is_open())
                    instance->_file.close();
            }

            /// \brief In case of the logger mode set to FILE, changes the file path to write to.
            /// \param filepath : path of the file to write to.
            static void setFileOutput(const std::string &filepath)
            {
                Logger *instance = getInstance();

                if (instance->_file.is_open())
                    instance->_file.close();
                instance->_file.open(filepath, std::ofstream::out | std::ofstream::app);
            }

        private:
            
            /// \brief Inaccessible singleton instance outside the class.
            /// \param mode : mode of the logger.
            /// \param flags : flags of the logger.
            static Logger *getInstance(mode mode = STANDARD, char flags = Flags::all_on)
            {
                static std::unique_ptr<Logger> loggerObject(new Logger(flags, mode));

                return loggerObject.get();
            }

            /// \brief Inaccessible Ctor.
            /// \param filepath : file path of the file to write to.
            /// \param flags : flags of the logger.
            /// \param mode : mode of the logger.
            Logger(const std::string &filepath, char flags = Flags::all_on, mode mode = FILE);

            /// \brief Inaccessible Ctor.
            /// \param flags : flags of the logger.
            /// \param mode : mode of the logger.
            Logger(char flags = Flags::all_on, mode mode = STANDARD);

            /// \brief Emptying the task queue by calling the printDebug method.
            void writeContent();

            /// \brief Get a string of the current time.
            /// \return A string of the current time.
            std::string getCurrentTimeString();

            /// \brief Generate the message passed as parameter to a file.
            /// \param type : the type of the message.
            /// \param message : the message that we want to display.
            /// \param where : from where the debug as been executed.
            void generateMessageInFile(type type, const std::string &message, const std::string &where);

            /// \brief Generate the message passed as parameter to the standard output.
            /// \param type : the type of the message.
            /// \param message : the message that we want to display.
            /// \param where : from where the debug as been executed.
            void generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where);

            /// \brief Get a formated string by the type of the message. (for a file)
            /// \param type : the type of the message.
            std::string getMessageFromType(type type) {return type == INFO ? INFO_MESSAGE :
                                                              type == WARNING ? WARNING_MESSAGE :
                                                              type == ERROR ? ERROR_MESSAGE :
                                                              type == FATAL ? FATAL_MESSAGE : DEBUG_MESSAGE;};

            /// \brief Get a formated string by the type of the message. (colored for the standard output)
            /// \param type : the type of the message.
            std::string getMessageColorFromType(type type) {return type == INFO ? GREEN :
                                                                   type == WARNING ? YELLOW :
                                                                   type == ERROR ? RED :
                                                                   type == FATAL ? REDUNDERLINED : "";};

            /*! the mode of the logger */
            mode _mode;

            /*! the flags of the logger */
            char _flags;

            /*! the file to write to */
            std::ofstream _file;

            /*! the queue of tasks */
            std::queue<std::string> _queue;

            /*! the writing thread */
            std::thread _worker;

            /*! the mutex to write on files */
            std::mutex _notifiedMutex;

            /*! the condition variable to notifie the thread that a task as been added */
            std::condition_variable _condVar;
            
            /*! check of the thread as been notified */
            bool _bNotified;
            
            /*! check if the thread is still active */
            bool _bIsWorkerActive;

            /*! the current time */
            std::chrono::high_resolution_clock::time_point _time;
    };
}
