#pragma once

#include "json.hpp"

#include <functional>
#include <stop_token>
#include <string>

namespace AccountAuthentication
{
    using BrowserOpener = std::function<void(const std::string&)>;

    std::string NormalizeServerUrl(const std::string& rawServerUrl);
    std::string GenerateCodeVerifier();
    std::string GenerateCodeChallenge(const std::string& codeVerifier);
    std::string ExtractAccessCodeFromHttpRequest(const std::string& request);

    nlohmann::json BuildAccount(
        const std::string& serverUrl,
        const std::string& token,
        const std::string& refreshToken,
        const nlohmann::json& userAndServerInfo,
        bool isDefault);

    nlohmann::json Authenticate(
        const std::string& serverUrl,
        std::stop_token stopToken,
        const BrowserOpener& openBrowser);
}
