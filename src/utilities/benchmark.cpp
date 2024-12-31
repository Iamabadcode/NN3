#include <chrono>

#include "util.h"

using namespace std::chrono;

time_point<high_resolution_clock> start, end;

void timer::startTimer() 
{
	logger::consoleLog("Started high precision timer", INFO);
	start = high_resolution_clock::now();
}

void timer::endTimer() 
{
	end = high_resolution_clock::now();
	logger::consoleLog("Ended high precision timer", INFO);
}

double timer::getElapsedSeconds() 
{
	return duration_cast<duration<double>>(end - start).count();
}

long long timer::getElapsedTime(Units unit)
{
	switch (unit) {
	case NANOSECONDS:
		return duration_cast<nanoseconds>(end - start).count();
	case MICROSECONDS:
		return duration_cast<microseconds>(end - start).count();
	case MILLISECONDS:
		return duration_cast<milliseconds>(end - start).count();
	case SECONDS:
		return duration_cast<seconds>(end - start).count();
	default:
		ASSERT(false);
	}
}
