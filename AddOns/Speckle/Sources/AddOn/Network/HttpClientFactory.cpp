#include "HttpClientFactory.h"

#ifdef _WIN32
#include "WinHttpClient.h"
#elif defined(__APPLE__)
#include "MacHttpClient.h"
#endif

#include <stdexcept>

std::shared_ptr<IHttpClient> CreateHttpClient()
{
#ifdef _WIN32
    return std::make_shared<WinHttpClient>();
#elif defined(__APPLE__)
    return std::make_shared<MacHttpClient>();
#else
    throw std::runtime_error("This platform has no Speckle HTTP client implementation");
#endif
}
