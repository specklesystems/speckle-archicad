#include "AccountFactory.h"
#include "CryptoUtils.h"

#include <stdexcept>
#include <string>

namespace
{
    std::string TrimTrailingSlash(const std::string& url)
    {
        std::size_t end = url.size();
        while (end > 0 && url[end - 1] == '/')
            --end;
        return url.substr(0, end);
    }

    // ASCII lower-case, matching string.ToLowerInvariant() for the ASCII inputs
    // (email + url) the account id is computed from.
    std::string AsciiToLower(const std::string& in)
    {
        std::string out = in;
        for (char& c : out)
        {
            if (c >= 'A' && c <= 'Z')
                c = static_cast<char>(c - 'A' + 'a');
        }
        return out;
    }
}

AccountFactory::AccountFactory(std::shared_ptr<IHttpClient> http)
    : _http(std::move(http))
{
}

nlohmann::json AccountFactory::CreateAccount(
    const std::string& serverUrl,
    const std::string& token,
    const std::string& refreshToken,
    bool isFirstAccount)
{
    const std::string base = TrimTrailingSlash(serverUrl);

    // Single bootstrap query: the fields Speckle persists to Accounts.db.
    const char* query =
        "query { activeUser { id name email company avatar } "
        "serverInfo { name company description version migration { movedFrom movedTo } } }";

    nlohmann::json requestBody;
    requestBody["query"] = query;

    HttpResponse response = _http->PostJson(base + "/graphql", requestBody.dump(), token);
    if (!response.IsSuccess())
        throw std::runtime_error("Failed to fetch account info (HTTP " + std::to_string(response.statusCode) + ").");

    nlohmann::json parsed = nlohmann::json::parse(response.body);
    if (!parsed.contains("data") || parsed["data"].is_null())
        throw std::runtime_error("Unexpected response while fetching account info.");

    nlohmann::json data = parsed["data"];
    nlohmann::json activeUser = data.value("activeUser", nlohmann::json());
    if (activeUser.is_null())
        throw std::runtime_error("The server rejected the token (no active user).");

    nlohmann::json serverInfo = data.value("serverInfo", nlohmann::json::object());
    // These two are populated client-side (not returned by the GQL query),
    // matching Speckle.Sdk's AccountManager.
    serverInfo["url"] = base;
    serverInfo["frontend2"] = true;

    const std::string email = activeUser.value("email", std::string());
    const std::string id = CryptoUtils::Md5UpperHex(AsciiToLower(email + base));

    nlohmann::json account;
    account["id"] = id;
    account["token"] = token;
    account["refreshToken"] = refreshToken;
    account["isDefault"] = isFirstAccount;
    account["isOnline"] = true;
    account["serverInfo"] = serverInfo;
    account["userInfo"] = activeUser;
    return account;
}
