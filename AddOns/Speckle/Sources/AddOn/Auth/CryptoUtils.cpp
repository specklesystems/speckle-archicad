#include "CryptoUtils.h"

#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif
#else
#include <cstdlib>              // arc4random_buf (CSPRNG, no seeding/failure mode)
#include <CommonCrypto/CommonDigest.h>
#endif

#include "picosha2.h"

namespace
{
    const char kBase64Alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}

namespace CryptoUtils
{
    std::vector<std::uint8_t> RandomBytes(std::size_t count)
    {
        std::vector<std::uint8_t> buffer(count);
#ifdef _WIN32
        NTSTATUS status = BCryptGenRandom(
            nullptr,
            buffer.data(),
            static_cast<ULONG>(buffer.size()),
            BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        if (status != STATUS_SUCCESS)
            throw std::runtime_error("BCryptGenRandom failed");
#else
        arc4random_buf(buffer.data(), buffer.size());
#endif
        return buffer;
    }

    std::string Base64UrlEncode(const std::vector<std::uint8_t>& data)
    {
        std::string out;
        out.reserve(((data.size() + 2) / 3) * 4);

        std::size_t i = 0;
        while (i + 3 <= data.size())
        {
            std::uint32_t n = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
            out.push_back(kBase64Alphabet[(n >> 18) & 0x3F]);
            out.push_back(kBase64Alphabet[(n >> 12) & 0x3F]);
            out.push_back(kBase64Alphabet[(n >> 6) & 0x3F]);
            out.push_back(kBase64Alphabet[n & 0x3F]);
            i += 3;
        }

        std::size_t remaining = data.size() - i;
        if (remaining == 1)
        {
            std::uint32_t n = (data[i] << 16);
            out.push_back(kBase64Alphabet[(n >> 18) & 0x3F]);
            out.push_back(kBase64Alphabet[(n >> 12) & 0x3F]);
        }
        else if (remaining == 2)
        {
            std::uint32_t n = (data[i] << 16) | (data[i + 1] << 8);
            out.push_back(kBase64Alphabet[(n >> 18) & 0x3F]);
            out.push_back(kBase64Alphabet[(n >> 12) & 0x3F]);
            out.push_back(kBase64Alphabet[(n >> 6) & 0x3F]);
        }

        // Make url-safe: standard base64 -> base64url, padding already omitted.
        for (char& c : out)
        {
            if (c == '+') c = '-';
            else if (c == '/') c = '_';
        }
        return out;
    }

    std::string GenerateCodeVerifier()
    {
        return Base64UrlEncode(RandomBytes(32));
    }

    std::string ComputeCodeChallenge(const std::string& codeVerifier)
    {
        std::vector<std::uint8_t> digest(picosha2::k_digest_size);
        picosha2::hash256(codeVerifier.begin(), codeVerifier.end(), digest.begin(), digest.end());
        return Base64UrlEncode(digest);
    }

#ifdef _WIN32
    std::string Md5UpperHex(const std::string& asciiInput)
    {
        BCRYPT_ALG_HANDLE hAlg = nullptr;
        BCRYPT_HASH_HANDLE hHash = nullptr;

        try
        {
            if (BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_MD5_ALGORITHM, nullptr, 0) != STATUS_SUCCESS)
                throw std::runtime_error("BCryptOpenAlgorithmProvider(MD5) failed");

            if (BCryptCreateHash(hAlg, &hHash, nullptr, 0, nullptr, 0, 0) != STATUS_SUCCESS)
                throw std::runtime_error("BCryptCreateHash failed");

            if (BCryptHashData(
                    hHash,
                    reinterpret_cast<PUCHAR>(const_cast<char*>(asciiInput.data())),
                    static_cast<ULONG>(asciiInput.size()),
                    0) != STATUS_SUCCESS)
                throw std::runtime_error("BCryptHashData failed");

            std::uint8_t digest[16];
            if (BCryptFinishHash(hHash, digest, sizeof(digest), 0) != STATUS_SUCCESS)
                throw std::runtime_error("BCryptFinishHash failed");

            static const char* kHex = "0123456789ABCDEF";
            std::string out;
            out.reserve(32);
            for (std::uint8_t b : digest)
            {
                out.push_back(kHex[b >> 4]);
                out.push_back(kHex[b & 0x0F]);
            }

            BCryptDestroyHash(hHash);
            BCryptCloseAlgorithmProvider(hAlg, 0);
            return out;
        }
        catch (...)
        {
            if (hHash) BCryptDestroyHash(hHash);
            if (hAlg) BCryptCloseAlgorithmProvider(hAlg, 0);
            throw;
        }
    }
#else
    std::string Md5UpperHex(const std::string& asciiInput)
    {
        // MD5 is used here only for the SDK's account-id derivation
        // (UPPERCASE hex MD5(lower(email+url))), not for security.
        // CC_MD5 is deprecated for cryptographic use, which this is not.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        unsigned char digest[CC_MD5_DIGEST_LENGTH];
        CC_MD5(asciiInput.data(), static_cast<CC_LONG>(asciiInput.size()), digest);
#pragma clang diagnostic pop

        static const char* kHex = "0123456789ABCDEF";
        std::string out;
        out.reserve(CC_MD5_DIGEST_LENGTH * 2);
        for (unsigned char b : digest)
        {
            out.push_back(kHex[b >> 4]);
            out.push_back(kHex[b & 0x0F]);
        }
        return out;
    }
#endif
}
