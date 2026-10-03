#pragma once

#include <chrono>
#include <condition_variable>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

#include "UserCancelledException.h"

class IngestionHeartbeat
{
public:
    using Report = std::function<void(const std::string&)>;

    IngestionHeartbeat(Report report, std::string message,
        std::chrono::milliseconds interval = std::chrono::seconds(30))
        : report(std::move(report)), message(std::move(message)), interval(interval),
          worker([this] { Run(); })
    {
    }

    ~IngestionHeartbeat() { Stop(); }
    IngestionHeartbeat(const IngestionHeartbeat&) = delete;
    IngestionHeartbeat& operator=(const IngestionHeartbeat&) = delete;

    void SetMessage(const std::string& value)
    {
        std::lock_guard<std::mutex> lock(mutex);
        message = value;
    }

    void CheckCancellation()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (cancellation) std::rethrow_exception(cancellation);
    }

    void Stop()
    {
        {
            std::lock_guard<std::mutex> lock(mutex);
            stopping = true;
        }
        changed.notify_all();
        if (worker.joinable()) worker.join();
    }

private:
    void Run()
    {
        std::unique_lock<std::mutex> lock(mutex);
        while (!changed.wait_for(lock, interval, [this] { return stopping; }))
        {
            const auto currentMessage = message;
            lock.unlock();
            try
            {
                report(currentMessage);
            }
            catch (const UserCancelledException&)
            {
                lock.lock();
                cancellation = std::current_exception();
                return;
            }
            catch (const std::exception&)
            {
                // ENG-10394: transient progress failures must not abort an otherwise valid upload.
                std::clog << "Speckle ingestion progress update failed; retrying next interval\n";
            }
            lock.lock();
        }
    }

    Report report;
    std::string message;
    std::chrono::milliseconds interval;
    std::mutex mutex;
    std::condition_variable changed;
    bool stopping = false;
    std::exception_ptr cancellation;
    std::thread worker;
};
