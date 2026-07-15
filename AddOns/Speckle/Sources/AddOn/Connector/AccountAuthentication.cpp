#include "AccountAuthenticator.h"

#include "picosha2.h"

#ifdef __APPLE__
#include <CommonCrypto/CommonDigest.h>
#endif

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

#ifdef __APPLE__
#include <stdlib.h>
#endif

namespace
{
    std::string Base64UrlEncode(const std::vector<unsigned char>& bytes)
    {
        static constexpr char alphabet[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
        std::string encoded;
        encoded.reserve((bytes.size() * 4 + 2) / 3);

        std::size_t index = 0;
        while (index + 3 <= bytes.size())
        {
            const unsigned int value =
                (static_cast<unsigned int>(bytes[index]) << 16) |
                (static_cast<unsigned int>(bytes[index + 1]) << 8) |
                static_cast<unsigned int>(bytes[index + 2]);
            encoded.push_back(alphabet[(value >> 18) & 0x3f]);
            encoded.push_back(alphabet[(value >> 12) & 0x3f]);
            encoded.push_back(alphabet[(value >> 6) & 0x3f]);
            encoded.push_back(alphabet[value & 0x3f]);
            index += 3;
        }

        const std::size_t remaining = bytes.size() - index;
        if (remaining == 1)
        {
            const unsigned int value = static_cast<unsigned int>(bytes[index]) << 16;
            encoded.push_back(alphabet[(value >> 18) & 0x3f]);
            encoded.push_back(alphabet[(value >> 12) & 0x3f]);
        }
        else if (remaining == 2)
        {
            const unsigned int value =
                (static_cast<unsigned int>(bytes[index]) << 16) |
                (static_cast<unsigned int>(bytes[index + 1]) << 8);
            encoded.push_back(alphabet[(value >> 18) & 0x3f]);
            encoded.push_back(alphabet[(value >> 12) & 0x3f]);
            encoded.push_back(alphabet[(value >> 6) & 0x3f]);
        }

        return encoded;
    }

    int HexValue(char value)
    {
        if (value >= '0' && value <= '9')
            return value - '0';
        if (value >= 'a' && value <= 'f')
            return value - 'a' + 10;
        if (value >= 'A' && value <= 'F')
            return value - 'A' + 10;
        return -1;
    }

    std::string UrlDecode(const std::string& value)
    {
        std::string decoded;
        decoded.reserve(value.size());
        for (std::size_t index = 0; index < value.size(); ++index)
        {
            if (value[index] == '%' && index + 2 < value.size())
            {
                const int high = HexValue(value[index + 1]);
                const int low = HexValue(value[index + 2]);
                if (high >= 0 && low >= 0)
                {
                    decoded.push_back(static_cast<char>((high << 4) | low));
                    index += 2;
                    continue;
                }
            }
            decoded.push_back(value[index] == '+' ? ' ' : value[index]);
        }
        return decoded;
    }

    std::string FindQueryParameter(
        const std::string& query,
        const std::string& parameterName)
    {
        std::size_t start = 0;
        while (start <= query.size())
        {
            const std::size_t end = query.find('&', start);
            const std::string item = query.substr(
                start,
                end == std::string::npos ? std::string::npos : end - start);
            const std::size_t separator = item.find('=');
            const std::string name = UrlDecode(item.substr(0, separator));
            if (name == parameterName)
                return separator == std::string::npos
                    ? std::string{}
                    : UrlDecode(item.substr(separator + 1));
            if (end == std::string::npos)
                break;
            start = end + 1;
        }
        return {};
    }

    std::string Md5Uppercase(const std::string& value)
    {
#ifdef __APPLE__
        unsigned char digest[CC_MD5_DIGEST_LENGTH];
        CC_MD5(value.data(), static_cast<CC_LONG>(value.size()), digest);

        std::ostringstream result;
        result << std::uppercase << std::hex << std::setfill('0');
        for (unsigned char byte : digest)
            result << std::setw(2) << static_cast<unsigned int>(byte);
        return result.str();
#else
        throw std::runtime_error("Native Speckle account authentication is not supported on this platform");
#endif
    }
}

std::string AccountAuthentication::NormalizeServerUrl(
    const std::string& rawServerUrl)
{
    std::string serverUrl = rawServerUrl;
    while (!serverUrl.empty() && serverUrl.back() == '/')
        serverUrl.pop_back();

    if (serverUrl.find_first_of("?#") != std::string::npos)
        throw std::invalid_argument("The Speckle server URL must not contain a query or fragment");

    const std::size_t schemeEnd = serverUrl.find("://");
    if (schemeEnd == std::string::npos)
        throw std::invalid_argument("The Speckle server URL is invalid");
    const std::string scheme = serverUrl.substr(0, schemeEnd);
    const std::size_t authorityStart = schemeEnd + 3;
    const std::size_t authorityEnd = serverUrl.find('/', authorityStart);
    const std::string authority = serverUrl.substr(
        authorityStart,
        authorityEnd == std::string::npos
            ? std::string::npos
            : authorityEnd - authorityStart);
    if (authority.empty() || authorityEnd != std::string::npos)
        throw std::invalid_argument("The Speckle server URL must be an origin without a path");

    const bool isLoopback =
        authority == "localhost" || authority.starts_with("localhost:") ||
        authority == "127.0.0.1" || authority.starts_with("127.0.0.1:") ||
        authority == "[::1]" || authority.starts_with("[::1]:");
    if (scheme != "https" && !(scheme == "http" && isLoopback))
        throw std::invalid_argument(
            "The Speckle server must use HTTPS (HTTP is allowed only for loopback development servers)");

    return serverUrl;
}

std::string AccountAuthentication::GenerateCodeVerifier()
{
#ifdef __APPLE__
    std::vector<unsigned char> randomBytes(32);
    arc4random_buf(randomBytes.data(), randomBytes.size());
    return Base64UrlEncode(randomBytes);
#else
    throw std::runtime_error("Native Speckle account authentication is not supported on this platform");
#endif
}

std::string AccountAuthentication::GenerateCodeChallenge(
    const std::string& codeVerifier)
{
    std::vector<unsigned char> digest(picosha2::k_digest_size);
    picosha2::hash256(codeVerifier, digest);
    return Base64UrlEncode(digest);
}

std::string AccountAuthentication::ExtractAccessCodeFromHttpRequest(
    const std::string& request)
{
    const std::size_t firstSpace = request.find(' ');
    const std::size_t secondSpace = firstSpace == std::string::npos
        ? std::string::npos
        : request.find(' ', firstSpace + 1);
    if (firstSpace == std::string::npos || secondSpace == std::string::npos ||
        request.substr(0, firstSpace) != "GET")
        throw std::runtime_error("The authentication callback was invalid");

    const std::string target = request.substr(
        firstSpace + 1,
        secondSpace - firstSpace - 1);
    const std::size_t queryStart = target.find('?');
    const std::string query = queryStart == std::string::npos
        ? std::string{}
        : target.substr(queryStart + 1);

    if (FindQueryParameter(query, "denied") == "true")
        throw std::runtime_error("Authentication was denied");

    const std::string accessCode = FindQueryParameter(query, "access_code");
    if (accessCode.empty())
        throw std::runtime_error("The authentication callback did not contain an access code");
    return accessCode;
}

nlohmann::json AccountAuthentication::BuildAccount(
    const std::string& serverUrl,
    const std::string& token,
    const std::string& refreshToken,
    const nlohmann::json& userAndServerInfo,
    bool isDefault)
{
    if (!userAndServerInfo.is_object() ||
        userAndServerInfo.contains("errors") ||
        !userAndServerInfo.contains("data") ||
        !userAndServerInfo["data"].is_object())
        throw std::runtime_error("The server returned invalid account information");

    const auto& data = userAndServerInfo["data"];
    if (!data.contains("activeUser") || !data["activeUser"].is_object() ||
        !data["activeUser"].contains("email") ||
        !data["activeUser"]["email"].is_string() ||
        !data.contains("serverInfo") || !data["serverInfo"].is_object())
        throw std::runtime_error("The server returned incomplete account information");

    nlohmann::json serverInfo = data["serverInfo"];
    serverInfo["url"] = serverUrl;
    const std::string id = Md5Uppercase(
        data["activeUser"]["email"].get<std::string>() + serverUrl);

    return {
        { "id", id },
        { "token", token },
        { "refreshToken", refreshToken },
        { "isDefault", isDefault },
        { "isOnline", true },
        { "serverInfo", std::move(serverInfo) },
        { "userInfo", data["activeUser"] }
    };
}
