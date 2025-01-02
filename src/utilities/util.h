#pragma once
#include <string>

#include "util_Config.h"


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
	[[nodiscard]] const unsigned char getLogLevel();
}

namespace math
{
	struct vec2 { float x, y; };
	struct vec2i { int x, y; };

	[[nodiscard]] float random(vec2) noexcept;
	[[nodiscard]] float random_int(vec2i) noexcept;

	[[nodiscard]] inline float ReLU(float x) noexcept { return x > 0 ? x : 0; }
	[[nodiscard]] inline float ReLU_d(float x) noexcept { return (x > 0.0f) ? 1.0f : 0.0f; }
	[[nodiscard]] inline float sigmoid(float x) noexcept { return 1.0f / (1.0f + exp(-x)); }
	[[nodiscard]] inline float sigmoid_d(float x) noexcept { float sigmoid_value = (1.0f / (1.0f + exp(-x))); return sigmoid_value * (1.0f - sigmoid_value); }
	[[nodiscard]] inline float tanh(float x) noexcept { return tanh(x); }
	[[nodiscard]] inline float tanh_d(float x) noexcept { float tanh_value = tanh(x); return 1.0f - (tanh_value * tanh_value); }

}

enum Units : unsigned char
{
	NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS
};
namespace timer 
{
	void startTimer();
	void endTimer();
	[[nodiscard]] double getElapsedSeconds();
	[[nodiscard]] long long getElapsedTime(Units unit);
}

// SIMD
[[nodiscard]] const bool check_avx512_support();
[[nodiscard]] const bool check_avx_support();
void logSIMDSupport();
