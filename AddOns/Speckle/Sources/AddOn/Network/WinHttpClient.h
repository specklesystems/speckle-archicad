#pragma once

#include "IHttpClient.h"

// WinHTTP-based IHttpClient (Windows only). Uses the OS TLS stack and the
// machine's WinHTTP proxy settings; no vendored networking dependencies.
class WinHttpClient : public IHttpClient
{
public:
    HttpResponse PostJson(
        const std::string& url,
        const std::string& jsonBody,
        const std::string& bearerToken) override;

    HttpResponse PutFile(
        const std::string& url,
        const std::string& filePath,
        const std::map<std::string, std::string>& extraHeaders,
        const UploadProgress& progress = nullptr) override;

    HttpResponse Get(
        const std::string& url,
        const std::string& bearerToken) override;

    HttpResponse GetToFile(
        const std::string& url,
        const std::string& bearerToken,
        const std::string& filePath) override;
};
