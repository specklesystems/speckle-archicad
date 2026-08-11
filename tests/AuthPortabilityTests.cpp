#include "CryptoUtils.h"
#include "LoopbackListener.h"

#include <cassert>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

// Exercises the platform-specific halves of the Auth/ module (crypto + loopback
// listener) so the macOS port can be validated without an Archicad build.
int main()
{
    // PKCE code_challenge: RFC 7636 appendix B test vector.
    assert(CryptoUtils::ComputeCodeChallenge("dBjftJeZ4CVP-mB92K27uhbUJU1p1r_wW1gFWFOEjXk")
           == "E9Melhoa2OwvFrEMTJguCHaoeK1t8URWbuGJSstw-cM");

    // Account-id MD5 must be bit-exact across platforms: the id derived from
    // lower(email+url) dedups accounts against Speckle Manager's Accounts.db.
    assert(CryptoUtils::Md5UpperHex("hello") == "5D41402ABC4B2A76B9719D911017C592");
    assert(CryptoUtils::Md5UpperHex("test@example.comhttps://app.speckle.systems")
           == "B759D165B6732C17179C6654A0167DF1");

    // 32 random bytes -> 43 base64url chars (no padding), and no two alike.
    const auto a = CryptoUtils::GenerateCodeVerifier();
    const auto b = CryptoUtils::GenerateCodeVerifier();
    assert(a.size() == 43 && b.size() == 43 && a != b);
    std::cout << "CryptoUtils tests passed" << std::endl;

    // Loopback round-trip: bind, catch the redirect, percent-decode the code.
    {
        LoopbackListener listener(29355);
        std::thread browser([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::system("curl -s 'http://127.0.0.1:29355/?access_code=abc%2F123&foo=bar' > /dev/null");
        });
        const std::string code = listener.WaitForAccessCode(5, [] { return false; });
        browser.join();
        assert(code == "abc/123");
    }
    std::cout << "LoopbackListener tests passed" << std::endl;

    return 0;
}
