#include "WinHttpClient.h"

#ifdef _WIN32

#include <windows.h>
#include <winhttp.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <vector>

#pragma comment(lib, "winhttp.lib")

namespace
{
    std::wstring Widen(const std::string& s)
    {
        if (s.empty())
            return {};
        int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), nullptr, 0);
        std::wstring w(len, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), w.data(), len);
        return w;
    }

    std::string Narrow(const std::wstring& w)
    {
        if (w.empty())
            return {};
        int len = WideCharToMultiByte(CP_UTF8, 0, w.data(), static_cast<int>(w.size()), nullptr, 0, nullptr, nullptr);
        std::string s(len, '\0');
        WideCharToMultiByte(CP_UTF8, 0, w.data(), static_cast<int>(w.size()), s.data(), len, nullptr, nullptr);
        return s;
    }

    struct HInternet
    {
        HINTERNET h = nullptr;
        explicit HInternet(HINTERNET handle) : h(handle) {}
        ~HInternet() { if (h) WinHttpCloseHandle(h); }
        HInternet(const HInternet&) = delete;
        HInternet& operator=(const HInternet&) = delete;
        HInternet(HInternet&& other) noexcept : h(other.h) { other.h = nullptr; }
        HInternet& operator=(HInternet&& other) noexcept
        {
            if (this != &other)
            {
                if (h) WinHttpCloseHandle(h);
                h = other.h;
                other.h = nullptr;
            }
            return *this;
        }
        explicit operator bool() const { return h != nullptr; }
    };

    struct ParsedUrl
    {
        std::wstring host;
        std::wstring path; // path + query
        INTERNET_PORT port = 443;
        bool secure = true;
    };

    ParsedUrl ParseUrl(const std::string& url)
    {
        std::wstring wide = Widen(url);
        URL_COMPONENTS uc{};
        uc.dwStructSize = sizeof(uc);
        uc.dwHostNameLength = static_cast<DWORD>(-1);
        uc.dwUrlPathLength = static_cast<DWORD>(-1);
        uc.dwExtraInfoLength = static_cast<DWORD>(-1);
        if (!WinHttpCrackUrl(wide.c_str(), static_cast<DWORD>(wide.size()), 0, &uc))
            throw std::runtime_error("Invalid URL: " + url);

        ParsedUrl parsed;
        parsed.host.assign(uc.lpszHostName, uc.dwHostNameLength);
        parsed.path.assign(uc.lpszUrlPath, uc.dwUrlPathLength);
        if (uc.lpszExtraInfo && uc.dwExtraInfoLength > 0)
            parsed.path.append(uc.lpszExtraInfo, uc.dwExtraInfoLength);
        if (parsed.path.empty())
            parsed.path = L"/";
        parsed.port = uc.nPort;
        parsed.secure = uc.nScheme == INTERNET_SCHEME_HTTPS;
        return parsed;
    }

    HttpResponse ReadResponse(HINTERNET request)
    {
        if (!WinHttpReceiveResponse(request, nullptr))
            throw std::runtime_error("WinHttpReceiveResponse failed, error " + std::to_string(GetLastError()));

        HttpResponse response;

        DWORD status = 0;
        DWORD statusSize = sizeof(status);
        WinHttpQueryHeaders(
            request,
            WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
            WINHTTP_HEADER_NAME_BY_INDEX,
            &status,
            &statusSize,
            WINHTTP_NO_HEADER_INDEX);
        response.statusCode = static_cast<int>(status);

        // Raw headers -> lowercase-keyed map (the uploader needs the ETag).
        DWORD headerSize = 0;
        WinHttpQueryHeaders(
            request, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX,
            WINHTTP_NO_OUTPUT_BUFFER, &headerSize, WINHTTP_NO_HEADER_INDEX);
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER && headerSize > 0)
        {
            std::wstring rawHeaders(headerSize / sizeof(wchar_t), L'\0');
            if (WinHttpQueryHeaders(
                    request, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX,
                    rawHeaders.data(), &headerSize, WINHTTP_NO_HEADER_INDEX))
            {
                std::string all = Narrow(rawHeaders);
                size_t pos = 0;
                while (pos < all.size())
                {
                    size_t eol = all.find("\r\n", pos);
                    if (eol == std::string::npos)
                        eol = all.size();
                    std::string line = all.substr(pos, eol - pos);
                    pos = eol + 2;
                    size_t colon = line.find(':');
                    if (colon == std::string::npos)
                        continue;
                    std::string key = line.substr(0, colon);
                    std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                    std::string value = line.substr(colon + 1);
                    size_t start = value.find_first_not_of(' ');
                    if (start != std::string::npos)
                        value = value.substr(start);
                    response.headers[key] = value;
                }
            }
        }

        for (;;)
        {
            DWORD available = 0;
            if (!WinHttpQueryDataAvailable(request, &available))
                throw std::runtime_error("WinHttpQueryDataAvailable failed, error " + std::to_string(GetLastError()));
            if (available == 0)
                break;
            std::vector<char> chunk(available);
            DWORD read = 0;
            if (!WinHttpReadData(request, chunk.data(), available, &read))
                throw std::runtime_error("WinHttpReadData failed, error " + std::to_string(GetLastError()));
            response.body.append(chunk.data(), read);
        }

        return response;
    }

    HInternet OpenSession()
    {
        HInternet session(WinHttpOpen(
            L"Speckle-Archicad",
            WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0));
        if (!session)
            throw std::runtime_error("WinHttpOpen failed, error " + std::to_string(GetLastError()));
        // Generous timeouts: parquet PUTs of large models can take a while.
        WinHttpSetTimeouts(session.h, 30000, 30000, 600000, 600000);
        return session;
    }
}

HttpResponse WinHttpClient::PostJson(
    const std::string& url,
    const std::string& jsonBody,
    const std::string& bearerToken)
{
    ParsedUrl parsed = ParseUrl(url);
    HInternet session = OpenSession();

    HInternet connection(WinHttpConnect(session.h, parsed.host.c_str(), parsed.port, 0));
    if (!connection)
        throw std::runtime_error("WinHttpConnect failed, error " + std::to_string(GetLastError()));

    HInternet request(WinHttpOpenRequest(
        connection.h, L"POST", parsed.path.c_str(), nullptr,
        WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES,
        parsed.secure ? WINHTTP_FLAG_SECURE : 0));
    if (!request)
        throw std::runtime_error("WinHttpOpenRequest failed, error " + std::to_string(GetLastError()));

    std::wstring headers = L"Content-Type: application/json\r\n";
    if (!bearerToken.empty())
        headers += L"Authorization: Bearer " + Widen(bearerToken) + L"\r\n";

    if (!WinHttpSendRequest(
            request.h,
            headers.c_str(), static_cast<DWORD>(-1),
            const_cast<char*>(jsonBody.data()), static_cast<DWORD>(jsonBody.size()),
            static_cast<DWORD>(jsonBody.size()), 0))
        throw std::runtime_error("WinHttpSendRequest failed, error " + std::to_string(GetLastError()));

    return ReadResponse(request.h);
}

HttpResponse WinHttpClient::PutFile(
    const std::string& url,
    const std::string& filePath,
    const std::map<std::string, std::string>& extraHeaders)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file)
        throw std::runtime_error("Cannot open file for upload: " + filePath);
    const std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    ParsedUrl parsed = ParseUrl(url);
    HInternet session = OpenSession();

    HInternet connection(WinHttpConnect(session.h, parsed.host.c_str(), parsed.port, 0));
    if (!connection)
        throw std::runtime_error("WinHttpConnect failed, error " + std::to_string(GetLastError()));

    HInternet request(WinHttpOpenRequest(
        connection.h, L"PUT", parsed.path.c_str(), nullptr,
        WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES,
        parsed.secure ? WINHTTP_FLAG_SECURE : 0));
    if (!request)
        throw std::runtime_error("WinHttpOpenRequest failed, error " + std::to_string(GetLastError()));

    std::wstring headers = L"Content-Type: application/octet-stream\r\n";
    for (const auto& kv : extraHeaders)
        headers += Widen(kv.first) + L": " + Widen(kv.second) + L"\r\n";

    if (!WinHttpSendRequest(
            request.h,
            headers.c_str(), static_cast<DWORD>(-1),
            WINHTTP_NO_REQUEST_DATA, 0,
            static_cast<DWORD>(fileSize), 0))
        throw std::runtime_error("WinHttpSendRequest failed, error " + std::to_string(GetLastError()));

    // Stream the file in 1 MB chunks so large parquet files never load whole into memory.
    std::vector<char> buffer(1024 * 1024);
    std::streamsize remaining = fileSize;
    while (remaining > 0)
    {
        const std::streamsize toRead = std::min<std::streamsize>(remaining, static_cast<std::streamsize>(buffer.size()));
        file.read(buffer.data(), toRead);
        if (file.gcount() != toRead)
            throw std::runtime_error("Short read while uploading: " + filePath);
        DWORD written = 0;
        if (!WinHttpWriteData(request.h, buffer.data(), static_cast<DWORD>(toRead), &written) || written != static_cast<DWORD>(toRead))
            throw std::runtime_error("WinHttpWriteData failed, error " + std::to_string(GetLastError()));
        remaining -= toRead;
    }

    return ReadResponse(request.h);
}

#endif // _WIN32
