#include "OAuthFlow.h"
#include "CryptoUtils.h"
#include "LoopbackListener.h"
#include "UrlLauncher.h"

#include <stdexcept>

#include "json.hpp"

namespace
{
    // Public-client identity + loopback redirect, matching AuthApp.ConnectorsV3.
    const char* kAppId = "connectrV3";
    const char* kAppSecret = "connectrV3";
    const unsigned short kRedirectPort = 29355;

    std::string TrimTrailingSlash(const std::string& url)
    {
        std::size_t end = url.size();
        while (end > 0 && url[end - 1] == '/')
            --end;
        return url.substr(0, end);
    }
}

OAuthFlow::OAuthFlow(std::shared_ptr<IHttpClient> http)
    : _http(std::move(http))
{
}

OAuthTokens OAuthFlow::Authenticate(
    const std::string& serverUrl,
    int timeoutSeconds,
    const std::function<bool()>& isCanceled)
{
    const std::string base = TrimTrailingSlash(serverUrl);

    // 1. Probe for the modern PKCE endpoint; fall back to the legacy one.
    bool useNewEndpoint = false;
    try
    {
        HttpResponse probe = _http->Get(base + "/oauth/token", "");
        useNewEndpoint = (probe.statusCode == 200);
    }
    catch (...)
    {
        useNewEndpoint = false;
    }

    // 2. PKCE code_verifier (and, for the new flow, its S256 challenge).
    const std::string codeVerifier = CryptoUtils::GenerateCodeVerifier();

    std::string authUrl;
    std::string tokenEndpoint;
    if (useNewEndpoint)
    {
        const std::string challenge = CryptoUtils::ComputeCodeChallenge(codeVerifier);
        authUrl = base + "/authn/verify/" + kAppId + "/" + challenge + "?code_challenge_method=S256";
        tokenEndpoint = base + "/oauth/token";
    }
    else
    {
        authUrl = base + "/authn/verify/" + std::string(kAppId) + "/" + codeVerifier;
        tokenEndpoint = base + "/auth/token";
    }

    // 3. Start the redirect listener *before* opening the browser so we never
    //    miss a fast redirect.
    LoopbackListener listener(kRedirectPort);

    // 4. Hand off to the system browser and wait for the redirect.
    UrlLauncher::Open(authUrl);
    const std::string accessCode = listener.WaitForAccessCode(timeoutSeconds, isCanceled);

    // 5. Exchange the access code for tokens.
    nlohmann::json body;
    body["appId"] = kAppId;
    body["accessCode"] = accessCode;
    if (useNewEndpoint)
    {
        body["codeVerifier"] = codeVerifier;
    }
    else
    {
        body["appSecret"] = kAppSecret;
        body["challenge"] = codeVerifier;
    }

    HttpResponse response = _http->PostJson(tokenEndpoint, body.dump(), "");
    if (!response.IsSuccess())
        throw std::runtime_error("Token exchange failed (HTTP " + std::to_string(response.statusCode) + ").");

    nlohmann::json parsed = nlohmann::json::parse(response.body);
    OAuthTokens tokens;
    tokens.token = parsed.at("token").get<std::string>();
    tokens.refreshToken = parsed.value("refreshToken", std::string());
    return tokens;
}
