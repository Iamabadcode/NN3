#include <iostream>
#include <string>

#include "util.h"

using namespace std;

constexpr unsigned int WINDOWS_DEFAULT_COLOR_ID = 97;
constexpr unsigned int WINDOWS_COLOR_ID_WARNING = 93;
constexpr unsigned int WINDOWS_COLOR_ID_ERROR = 91;

unsigned char log_level = NULL;

void setConsoleColor(unsigned int color_id)  
{
	if constexpr (LOG_WITH_COLOR == 1) 
	{
		cout << "\033[" << color_id << "m";
	}
}

void log_config::setLogLevel(const unsigned char t_log_level) 
{
	log_level = t_log_level;
}

const unsigned char log_config::getLogLevel() 
{
	return log_level;
}

void logger::newLine()
{
	if(log_level >= DEBUG)std::cout << "\n";
}

void logger::consoleLog(std::string message)
{
	if (log_level >= DEBUG) cout << message;
}

void logger::consoleLog(const char* message) 
{
	if (log_level >= DEBUG) cout << message;
}

void logger::consoleLog(std::string message, LogLevel level)
{
	switch (level)
	{
	case NULL:
		return;
	case INFO:		if (log_level < INFO) return;
		cout << "> " << message << endl; break;

	case SUB_INFO:		if (log_level < INFO) return;
		cout << "	> " << message << endl; break;

	case DEBUG:		if (log_level < DEBUG) return;
		cout << "#    " << message << endl; break;

	case WARNING:	if (log_level < WARNING) return;
		setConsoleColor(WINDOWS_COLOR_ID_WARNING);
		cout << "[WARNING] : " << message << endl; break;

	case ERROR:		if (log_level < ERROR) return;
		setConsoleColor(WINDOWS_COLOR_ID_ERROR);
		cout << "[ERROR] : " << message << endl; break;


	default:
		break;
	}
	setConsoleColor(WINDOWS_DEFAULT_COLOR_ID);
}

void logger::consoleLog(const char* message, LogLevel level) 
{
	switch (level)
	{
	case NULL:
		return;
	case INFO:		if (log_level < INFO) return;
		cout << "> " << message << endl; break;

	case SUB_INFO:		if (log_level < INFO) return;
		cout << "	> " << message << endl; break;

	case DEBUG:		if (log_level < DEBUG) return;
		cout << "#    " << message << endl; break;

	case WARNING:	if (log_level < WARNING) return;
		setConsoleColor(WINDOWS_COLOR_ID_WARNING);
		cout << "[WARNING] : " << message << endl; break;

	case ERROR:		if (log_level < ERROR) return;
		setConsoleColor(WINDOWS_COLOR_ID_ERROR);
		cout << "[ERROR] : " << message << endl; break;
		
		
	default:
		break;
	}
	setConsoleColor(WINDOWS_DEFAULT_COLOR_ID);
}

