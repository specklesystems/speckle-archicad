#pragma once

#include <string>
#include <vector>
#include <cstdint>

// Small crypto helpers for the native OAuth (PKCE) account flow.
// Windows-only: random bytes and MD5 come from CNG (bcrypt); SHA-256 reuses
// the vendored picosha2. Mirrors Speckle.Sdk's AuthFlow / Crypt helpers.
namespace CryptoUtils
{
    // Cryptographically strong random bytes (BCryptGenRandom).
    std::vector<std::uint8_t> RandomBytes(std::size_t count);

    // Base64url (RFC 4648 §5): '+'->'-', '/'->'_', padding '=' stripped.
    std::string Base64UrlEncode(const std::vector<std::uint8_t>& data);

    // PKCE code_verifier: base64url of 32 random bytes.
    std::string GenerateCodeVerifier();

    // PKCE code_challenge: base64url(SHA-256(verifier)) — the S256 method.
    std::string ComputeCodeChallenge(const std::string& codeVerifier);

    // MD5 of the ASCII bytes of input, formatted as 32 UPPERCASE hex chars.
    // Matches Speckle.Sdk Crypt.Md5(input, "X2"). NOTE: caller must pass the
    // already-lower-cased string (the SDK lower-cases before hashing).
    std::string Md5UpperHex(const std::string& asciiInput);
}
