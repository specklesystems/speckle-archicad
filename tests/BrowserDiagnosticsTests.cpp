#include "BrowserDiagnostics.h"

#include <cassert>
#include <iostream>

int main()
{
    assert(BrowserDiagnostics::SanitizeURL("https://user:password@dui.speckle.systems/path?access_code=secret#token")
        == "https://dui.speckle.systems/path");
    assert(BrowserDiagnostics::SanitizeURL("http://user:password@[::1]:1234/path?token=secret")
        == "http://[::1]:1234/path");
    assert(BrowserDiagnostics::SanitizeURL("https://dui.speckle.systems?token=user@secret/path")
        == "https://dui.speckle.systems");
    assert(BrowserDiagnostics::SanitizeURL("https://dui.speckle.systems/path\nsecret")
        == "https://dui.speckle.systems/path");
    assert(BrowserDiagnostics::SanitizeURL("data:text/html,private payload") == "<opaque URL>");
    assert(BrowserDiagnostics::SanitizeURL("about:blank") == "<opaque URL>");
    assert(BrowserDiagnostics::SanitizeURL("private payload") == "<invalid URL>");
    std::cout << "Browser diagnostics URL tests passed\n";
}
