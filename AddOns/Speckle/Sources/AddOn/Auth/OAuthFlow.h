#pragma once

#include <functional>
#include <memory>
#include <string>

#include "IHttpClient.h"

struct OAuthTokens
{
    std::string token;
    std::string refreshToken;
};

// Native port of Speckle.Sdk's AuthFlow: a browser-based PKCE authorization-code
// flow. Probes for the new /oauth/token endpoint (falling back to the legacy
// /auth/token), opens the system browser at the server's authn page, catches the
// redirect on a loopback listener, and exchanges the access code for tokens.
// Talks to the server exclusively through IHttpClient (WinHTTP).
class OAuthFlow
{
public:
    explicit OAuthFlow(std::shared_ptr<IHttpClient> http);

    // Runs the whole flow synchronously. isCanceled is polled while waiting for
    // the browser redirect so the caller can abort (throws UserCancelledException).
    OAuthTokens Authenticate(
        const std::string& serverUrl,
        int timeoutSeconds,
        const std::function<bool()>& isCanceled);

private:
    std::shared_ptr<IHttpClient> _http;
};
