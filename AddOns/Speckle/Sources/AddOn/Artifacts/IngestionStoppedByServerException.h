#pragma once

#include <stdexcept>

// ENG-10394: the server's idle-timeout sweep sets cancellationRequested itself, so a
// server-side stop is not a user cancellation and must surface as an error.
class IngestionStoppedByServerException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};
