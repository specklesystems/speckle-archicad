#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

// Event class template that allows any callback signature with arguments.
template <typename... Args>
class Event {
public:
    using CallbackType = std::function<void(Args...)>;

    // Add a listener
    void operator+=(const CallbackType& listener) 
    {
        listeners.push_back(listener);
    }

    // Remove a listener
    void operator-=(const CallbackType& listener) 
    {
        listeners.erase(
            std::remove_if(listeners.begin(), listeners.end(),
                [&](const CallbackType& l) { return l.target_type() == listener.target_type(); }),
            listeners.end());
    }

    // Trigger the event, calling all listeners with provided arguments
    void operator()(Args... args) const 
    {
        for (const auto& listener : listeners) 
            listener(args...);
    }

private:
    std::vector<CallbackType> listeners;
};
