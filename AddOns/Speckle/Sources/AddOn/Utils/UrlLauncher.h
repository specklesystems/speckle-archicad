#pragma once

#include <string>

// Opens URLs in the user's default browser. Uses ShellExecuteW rather than
// system("start ...") so the full URL is preserved verbatim — cmd's `start`
// treats '&' as a command separator, which silently truncates query strings
// (e.g. OAuth ...?a=1&code_challenge_method=S256 loses the second param).
namespace UrlLauncher
{
    // Throws std::runtime_error if the shell fails to open the URL.
    void Open(const std::string& url);
}
