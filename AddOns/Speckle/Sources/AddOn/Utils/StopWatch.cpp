#include "StopWatch.h"
#include <sstream> // For std::ostringstream

// Get the singleton instance
StopWatch& StopWatch::GetInstance() 
{
    static StopWatch instance; // Guaranteed to be thread-safe in C++11 and later
    return instance;
}

// Private constructor
StopWatch::StopWatch() : isRunning(false) {}

// Start the timer
void StopWatch::Start() 
{
    startTime = std::chrono::high_resolution_clock::now();
    isRunning = true;
}

// Stop the timer, calculate the elapsed time, and reset
std::string StopWatch::Stop() 
{
    if (!isRunning) {
        return "Error: Stopwatch was not started.";
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    isRunning = false;

    // Calculate elapsed time in milliseconds
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    // Reset timer
    startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();

    // Format and return the result
    std::ostringstream oss;
    oss << "Elapsed: " << elapsedTime << " ms";
    return oss.str();
}
