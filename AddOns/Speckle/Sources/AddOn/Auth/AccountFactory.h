#pragma once

#include <memory>
#include <string>

#include "IHttpClient.h"
#include "json.hpp"

// Builds a Speckle Account (as JSON) from freshly minted tokens, mirroring
// Speckle.Sdk's AccountFactory: it runs one GraphQL query for the active user
// and server info, then assembles the exact JSON shape stored in Accounts.db,
// including the deterministic account id (MD5 of email+url) so accounts written
// here dedup with those written by Speckle Manager / other connectors.
class AccountFactory
{
public:
    explicit AccountFactory(std::shared_ptr<IHttpClient> http);

    // isFirstAccount seeds the "isDefault" flag (first account added is default).
    // Throws std::runtime_error if the token is rejected (no active user).
    nlohmann::json CreateAccount(
        const std::string& serverUrl,
        const std::string& token,
        const std::string& refreshToken,
        bool isFirstAccount);

private:
    std::shared_ptr<IHttpClient> _http;
};
