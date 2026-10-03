#include "IngestionHeartbeat.h"
#include "MacHttpClient.h"

#include <future>
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2) throw std::runtime_error("Expected stalled local HTTP endpoint");
    MacHttpClient client(1);
    std::promise<void> started;
    auto requestStarted = started.get_future();
    IngestionHeartbeat heartbeat([&](const std::string&)
    {
        started.set_value();
        client.PostJson(argv[1], "{}", "");
    }, "Converting elements", std::chrono::milliseconds(10));
    if (requestStarted.wait_for(std::chrono::seconds(2)) != std::future_status::ready)
        throw std::runtime_error("Heartbeat did not start its request");
    const auto before = std::chrono::steady_clock::now();
    heartbeat.Stop();
    const auto elapsed = std::chrono::steady_clock::now() - before;
    if (elapsed > std::chrono::milliseconds(2500))
        throw std::runtime_error("Stalled progress request delayed heartbeat shutdown past its deadline");
    std::cout << "PASS: in-flight macOS progress request times out and heartbeat joins within 2.5 seconds\n";
}
