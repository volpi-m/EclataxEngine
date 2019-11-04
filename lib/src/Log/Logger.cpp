/*
 *
 *   Lucas Tabis
 *   Logger class source file
 *
 *
 */

#include "Logger.hpp"

/*
 *   Construcor / Destructor.
 */

Debug::Logger::Logger(char flags, mode mode) : _mode(mode), _flags(flags), _bNotified(false), _bIsWorkerActive(true)
{
    _worker = std::thread(&Logger::writeContent, this);
}
Debug::Logger::Logger(const std::string &filePath, char flags, mode mode) : _mode(mode), _flags(flags), _file(filePath), _bNotified(false), _bIsWorkerActive(true)
{
    _worker = std::thread(&Logger::writeContent, this);
}

Debug::Logger::~Logger()
{
    if (_file.is_open())
        _file.close();
    _bNotified = true;
    _bIsWorkerActive = false;
    _condVar.notify_one();
    _worker.join();
}

void Debug::Logger::setFlags(char flags)
{
    _flags = flags;
}

void Debug::Logger::switchMode(mode mode, const std::string &filePath)
{
    _mode = mode;
    if (mode == FILE) {
        if (_file.is_open())
            _file.close();
        _file.open(filePath.empty() ? DEFAULT_LOG_FILE : filePath, std::ofstream::out | std::ofstream::app);
    } else
        if (_file.is_open())
            _file.close();
}

void Debug::Logger::writeContent()
{
    std::unique_lock<std::mutex> lock(_notifiedMutex);

    while (_bIsWorkerActive) {
        while (!_bNotified)
            _condVar.wait(lock);
        while (!_queue.empty() && _mode != OFF) {
            generateDebugMessage(_queue.front());
            _queue.pop();
        }
    _bNotified = false;
    }
}

//// USER ACCESS

/*
 *   generate a debug message with a type and where parameters.
 */

void Debug::Logger::generateDebugMessage(type type, const std::string &message, const std::string &where)
{
    if (_mode == STANDARD && !(_flags & type))
        generateMessageOnStandardOutput(type, message, where);
    else if (_mode == FILE && !(_flags & type))
        generateMessageInFile(type, message, where);
    _condVar.notify_one();
    _bNotified = true;
}

void Debug::Logger::generateDebugMessage(const std::string &formated)
{
    if (_mode == STANDARD)
        std::cout << formated << std::endl;
    else if (_mode == FILE && _file.is_open())
        _file << formated << std::endl;
}

void Debug::Logger::generateMessageInFile(type type, const std::string &message, const std::string &where)
{
    _queue.push(getCurrentTimeString() +
                getMessageFromType(type) + " " + message +  " in " + where);
}

void Debug::Logger::generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where)
{
    _queue.push(getCurrentTimeString() +
                getMessageColorFromType(type) +
                getMessageFromType(type) + CYAN + " " + message + WHITE + " in " + MAGENTA + where + WHITE);
}

std::string Debug::Logger::getCurrentTimeString()
{
    std::ostringstream oss;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    _time = std::chrono::high_resolution_clock::now();
    oss << (_mode == FILE ? std::put_time(&tm, "(%d-%m-%Y %Hh %Mm %Ss") : std::put_time(&tm, "(%Hh %Mm %Ss"));
    oss << " " << std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(_time.time_since_epoch()).count()) << "µs";
    return _mode == FILE ? oss.str() + ") " : BLUE + oss.str() + ") " + WHITE;
}
