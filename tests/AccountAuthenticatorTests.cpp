#include "AccountAuthenticator.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

int main()
{
    assert(AccountAuthentication::NormalizeServerUrl(
        "https://next.speckle.dev/") == "https://next.speckle.dev");
    assert(AccountAuthentication::NormalizeServerUrl(
        "http://127.0.0.1:3000/") == "http://127.0.0.1:3000");
    bool deceptiveLoopbackWasRejected = false;
    try
    {
        AccountAuthentication::NormalizeServerUrl(
            "http://localhost.example.com");
    }
    catch (const std::invalid_argument&)
    {
        deceptiveLoopbackWasRejected = true;
    }
    assert(deceptiveLoopbackWasRejected);

    const std::string firstRandomVerifier =
        AccountAuthentication::GenerateCodeVerifier();
    const std::string secondRandomVerifier =
        AccountAuthentication::GenerateCodeVerifier();
    assert(firstRandomVerifier.size() == 43);
    assert(secondRandomVerifier.size() == 43);
    assert(firstRandomVerifier != secondRandomVerifier);
    assert(firstRandomVerifier.find_first_not_of(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_") ==
        std::string::npos);

    // RFC 7636 Appendix B: this locks the connector to the standard S256
    // transformation used by Speckle's /oauth/token endpoint.
    const std::string verifier =
        "dBjftJeZ4CVP-mB92K27uhbUJU1p1r_wW1gFWFOEjXk";
    const std::string generatedChallenge =
        AccountAuthentication::GenerateCodeChallenge(verifier);
    assert(generatedChallenge ==
        "E9Melhoa2OwvFrEMTJguCHaoeK1t8URWbuGJSstw-cM");

    const std::string callbackRequest =
        "GET /?access_code=abc%2F123%2Bxyz HTTP/1.1\r\n"
        "Host: localhost:29355\r\n\r\n";
    assert(AccountAuthentication::ExtractAccessCodeFromHttpRequest(callbackRequest) ==
        "abc/123+xyz");

    bool deniedWasRejected = false;
    try
    {
        AccountAuthentication::ExtractAccessCodeFromHttpRequest(
            "GET /?denied=true HTTP/1.1\r\n\r\n");
    }
    catch (const std::runtime_error&)
    {
        deniedWasRejected = true;
    }
    assert(deniedWasRejected);

    const nlohmann::json graphQlResponse = {
        { "data", {
            { "activeUser", {
                { "id", "user-id" },
                { "name", "Test User" },
                { "email", "test@example.com" }
            } },
            { "serverInfo", {
                { "name", "Next" },
                { "version", "test" }
            } }
        } }
    };
    const auto account = AccountAuthentication::BuildAccount(
        "https://next.speckle.dev",
        "access-token",
        "refresh-token",
        graphQlResponse,
        true);

    assert(account["id"] == "772F7A00F3FCDE21D46965981BFC6E25");
    assert(account["serverInfo"]["url"] == "https://next.speckle.dev");
    assert(account["userInfo"]["id"] == "user-id");
    assert(account["token"] == "access-token");
    assert(account["refreshToken"] == "refresh-token");
    assert(account["isDefault"] == true);

    std::cout << "AccountAuthenticator protocol tests passed\n";
    return 0;
}
