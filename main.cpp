#include <iostream>
#include "Logger.hpp"
#include "Breakpoint.hpp"

int main()
{
	Debug::Logger *log = Debug::Logger::getInstance(Debug::STANDARD, Debug::Flags::fatal_off);
	{
		Debug::Breakpoint b("Logger class", "main", Debug::Flags::all_on);
		log->generateDebugMessage(Debug::DEBUG, "Just a regular debug message", "main");
		log->generateDebugMessage(Debug::INFO, "Info message", "main");
		log->generateDebugMessage(Debug::WARNING, "Warning message, attention !", "main");
		log->generateDebugMessage(Debug::ERROR, "Error", "main");
		log->generateDebugMessage(Debug::FATAL, "Fatal message, everything is going haywire !", "main");
	}
	Debug::Breakpoint b1("unused breakpoint", "main", Debug::Flags::debug_off);
	Debug::Breakpoint b2("Sleep", "main", Debug::Flags::all_on);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	log->generateDebugMessage(Debug::DEBUG, "debug message", "test::writeDebugMessage");
	return 0;
}
