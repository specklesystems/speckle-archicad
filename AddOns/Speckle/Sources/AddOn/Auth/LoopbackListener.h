#pragma once

#include <functional>
#include <string>

// Minimal single-shot HTTP loopback listener used to catch the OAuth redirect
// (http://localhost:29355/?access_code=...). Mirrors the HttpListener that
// Speckle.Sdk's AuthFlow spins up. Windows/Winsock only.
class LoopbackListener
{
public:
    // Binds 127.0.0.1:<port> and starts listening immediately (throws on failure,
    // e.g. the port is already taken by another in-flight sign-in).
    explicit LoopbackListener(unsigned short port);
    ~LoopbackListener();

    LoopbackListener(const LoopbackListener&) = delete;
    LoopbackListener& operator=(const LoopbackListener&) = delete;

    // Blocks until the browser hits the redirect URL, then returns the value of
    // the "access_code" query parameter. Writes a small HTML page back to the
    // browser before returning.
    //
    // isCanceled is polled (~5x/sec) so the caller can abort via the Archicad
    // process window; when it returns true a UserCancelledException is thrown.
    // Throws std::runtime_error on timeout, on a "?denied=true" redirect, or on
    // a socket error.
    std::string WaitForAccessCode(int timeoutSeconds, const std::function<bool()>& isCanceled);

private:
    unsigned long long _listenSocket; // SOCKET (kept opaque to avoid winsock.h in the header)
};
