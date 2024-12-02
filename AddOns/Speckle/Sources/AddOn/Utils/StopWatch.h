#pragma once

#define STOPWATCH StopWatch::GetInstance()

#include <string>
#include <chrono>
#include <memory>

class StopWatch 
{
public:
    // Public accessor for the singleton instance
    static StopWatch& GetInstance();

    // Starts the timer
    void Start();

    // Stops the timer and resets it, returning the elapsed time in milliseconds
    std::string Stop();

private:
    // Private constructor for singleton pattern
    StopWatch();

    // Deleted copy constructor and assignment operator to prevent duplication
    StopWatch(const StopWatch&) = delete;
    StopWatch& operator=(const StopWatch&) = delete;

    // Variables to store start and end times
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    bool isRunning; // Flag to check if timer is running
};
