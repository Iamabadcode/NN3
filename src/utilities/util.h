#pragma once
#include "util_Config.h"
#include <string>

#define ASSERT(x) if(!(x)) __debugbreak();

enum LogLevel : unsigned char
{
	ERROR = 1, WARNING, INFO, SUB_INFO, DEBUG
};
namespace logger 
{
	void newLine();
	void consoleLog(std::string message);
	void consoleLog(const char* message);
	void consoleLog(std::string message, LogLevel);
	void consoleLog(const char* message, LogLevel);
}
namespace log_config 
{
	void setLogLevel(const unsigned char t_log_level);
	const unsigned char getLogLevel();
}

namespace math
{
	struct vec2 { float x, y; };
	struct vec2i { int x, y; };

	float random(vec2);
	float random_int(vec2i);
}

enum Units : unsigned char
{
	NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS
};
namespace timer 
{
	void startTimer();
	void endTimer();
	double getElapsedSeconds();
	long long getElapsedTime(Units unit);
}

// SIMD
const bool check_avx512_support();
const bool check_avx_support();
void logSIMDSupport();
