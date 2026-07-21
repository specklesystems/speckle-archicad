#include "LoopbackListener.h"
#include "UserCancelledException.h"

#include <chrono>
#include <stdexcept>
#include <string>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

namespace
{
    // RAII for WSAStartup/WSACleanup. WinHTTP does its own networking, so the
    // OAuth listener owns the only Winsock usage in the add-on.
    struct WinsockScope
    {
        bool ok = false;
        WinsockScope()
        {
            WSADATA data;
            ok = (WSAStartup(MAKEWORD(2, 2), &data) == 0);
        }
        ~WinsockScope()
        {
            if (ok)
                WSACleanup();
        }
    };

    // The page the user sees in their browser once the redirect lands.
    const char* kSuccessBody =
        "<!doctype html><html><head><meta charset=\"utf-8\"><title>Speckle</title></head>"
        "<body style=\"font-family:sans-serif;text-align:center;padding-top:80px\">"
        "<h2>Authentication complete</h2>"
        "<p>You can close this window and return to Archicad.</p></body></html>";

    std::string PercentDecode(const std::string& in)
    {
        std::string out;
        out.reserve(in.size());
        for (std::size_t i = 0; i < in.size(); ++i)
        {
            if (in[i] == '%' && i + 2 < in.size())
            {
                auto hexVal = [](char c) -> int {
                    if (c >= '0' && c <= '9') return c - '0';
                    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
                    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
                    return -1;
                };
                int hi = hexVal(in[i + 1]);
                int lo = hexVal(in[i + 2]);
                if (hi >= 0 && lo >= 0)
                {
                    out.push_back(static_cast<char>((hi << 4) | lo));
                    i += 2;
                    continue;
                }
            }
            if (in[i] == '+')
                out.push_back(' ');
            else
                out.push_back(in[i]);
        }
        return out;
    }

    // Pulls a query parameter value out of a raw HTTP request line
    // ("GET /?access_code=abc&foo=bar HTTP/1.1").
    bool TryGetQueryParam(const std::string& requestLine, const std::string& key, std::string& value)
    {
        std::string needle = key + "=";
        std::size_t queryStart = requestLine.find('?');
        if (queryStart == std::string::npos)
            return false;

        std::size_t pos = requestLine.find(needle, queryStart);
        while (pos != std::string::npos)
        {
            // Ensure the match starts right after '?' or '&' (not mid-token).
            char prev = requestLine[pos - 1];
            if (prev == '?' || prev == '&')
            {
                std::size_t valStart = pos + needle.size();
                std::size_t valEnd = requestLine.find_first_of("& \t", valStart);
                if (valEnd == std::string::npos)
                    valEnd = requestLine.size();
                value = PercentDecode(requestLine.substr(valStart, valEnd - valStart));
                return true;
            }
            pos = requestLine.find(needle, pos + needle.size());
        }
        return false;
    }

    void SendHttpResponse(SOCKET client, const std::string& body)
    {
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n" + body;
        send(client, response.c_str(), static_cast<int>(response.size()), 0);
    }
}

LoopbackListener::LoopbackListener(unsigned short port)
    : _listenSocket(INVALID_SOCKET)
{
    static WinsockScope winsock; // one-time init for the process lifetime
    if (!winsock.ok)
        throw std::runtime_error("WSAStartup failed");

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
        throw std::runtime_error("Failed to create listener socket");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR)
    {
        closesocket(listenSocket);
        throw std::runtime_error(
            "Failed to bind 127.0.0.1:" + std::to_string(port) +
            " for the sign-in redirect (another sign-in may be in progress).");
    }

    if (listen(listenSocket, 1) == SOCKET_ERROR)
    {
        closesocket(listenSocket);
        throw std::runtime_error("Failed to listen on the sign-in redirect socket");
    }

    _listenSocket = listenSocket;
}

LoopbackListener::~LoopbackListener()
{
    if (_listenSocket != INVALID_SOCKET)
        closesocket(static_cast<SOCKET>(_listenSocket));
}

std::string LoopbackListener::WaitForAccessCode(int timeoutSeconds, const std::function<bool()>& isCanceled)
{
    SOCKET listenSocket = static_cast<SOCKET>(_listenSocket);
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);

    for (;;)
    {
        if (isCanceled && isCanceled())
            throw UserCancelledException("Sign-in cancelled");

        if (std::chrono::steady_clock::now() >= deadline)
            throw std::runtime_error("Timed out waiting for the browser sign-in to complete.");

        // Poll the listening socket with a short timeout so we can re-check
        // cancellation/deadline and keep the process window responsive.
        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(listenSocket, &readSet);
        timeval tv{};
        tv.tv_sec = 0;
        tv.tv_usec = 200 * 1000; // 200ms

        int ready = select(0, &readSet, nullptr, nullptr, &tv);
        if (ready == SOCKET_ERROR)
            throw std::runtime_error("select() failed on the sign-in redirect socket");
        if (ready == 0)
            continue; // nothing yet — loop and re-check cancel/deadline

        SOCKET client = accept(listenSocket, nullptr, nullptr);
        if (client == INVALID_SOCKET)
            continue;

        // Read the request (we only need the request line, which arrives first).
        std::string request;
        char buffer[2048];
        int received = recv(client, buffer, sizeof(buffer), 0);
        if (received > 0)
            request.assign(buffer, static_cast<std::size_t>(received));

        std::string firstLine = request.substr(0, request.find("\r\n"));

        std::string denied;
        if (TryGetQueryParam(firstLine, "denied", denied))
        {
            SendHttpResponse(client, kSuccessBody);
            closesocket(client);
            throw std::runtime_error("Sign-in was denied.");
        }

        std::string accessCode;
        if (TryGetQueryParam(firstLine, "access_code", accessCode) && !accessCode.empty())
        {
            SendHttpResponse(client, kSuccessBody);
            closesocket(client);
            return accessCode;
        }

        // Unrelated request (e.g. a favicon probe) — answer politely and keep waiting.
        SendHttpResponse(client, kSuccessBody);
        closesocket(client);
    }
}
