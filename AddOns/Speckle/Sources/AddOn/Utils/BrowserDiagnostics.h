#pragma once

#include <string>

namespace BrowserDiagnostics
{
    inline std::string SanitizeURL(const std::string& url)
    {
        const auto schemeEnd = url.find(':');
        if (schemeEnd == std::string::npos)
            return "<invalid URL>";
        const auto scheme = url.substr(0, schemeEnd);
        if (scheme != "http" && scheme != "https")
            return "<opaque URL>";
        if (url.substr(schemeEnd, 3) != "://")
            return "<invalid URL>";

        const auto authorityStart = schemeEnd + 3;
        const auto authorityEnd = url.find_first_of("/?#\r\n", authorityStart);
        auto authority = url.substr(authorityStart, authorityEnd - authorityStart);
        const auto userInfoEnd = authority.rfind('@');
        if (userInfoEnd != std::string::npos)
            authority.erase(0, userInfoEnd + 1);
        std::string path;
        if (authorityEnd != std::string::npos && url[authorityEnd] == '/')
            path = url.substr(authorityEnd, url.find_first_of("?#\r\n", authorityEnd) - authorityEnd);
        return scheme + "://" + authority + path;
    }

}
