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

    inline constexpr const char* ContextProbe = R"JS((() => {
        const safeURL = raw => {
            try { const u = new URL(raw); return u.protocol === 'https:' || u.protocol === 'http:' ? u.protocol + '//' + u.host + u.pathname : '<opaque URL>'; }
            catch (_) { return '<invalid URL>'; }
        };
        console.log('[DEBUG-ENG10393] context ' + JSON.stringify({
            url: safeURL(location.href),
            readyState: document.readyState,
            scripts: Array.from(document.scripts).map(s => safeURL(s.src)),
            bodyChildren: document.body ? document.body.children.length : 0,
            nuxtChildren: document.getElementById('__nuxt') ? document.getElementById('__nuxt').children.length : 0,
            CefSharp: typeof window.CefSharp,
            baseBinding: typeof window.baseBinding,
            accountsBinding: typeof window.accountsBinding,
            resources: performance.getEntriesByType('resource').filter(r => r.initiatorType === 'script' || r.initiatorType === 'link').map(r => ({url: safeURL(r.name), decodedBytes: r.decodedBodySize, transferredBytes: r.transferSize}))
        }));
    })())JS";
}
