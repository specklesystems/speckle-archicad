#pragma once

#include "IHttpClient.h"

// NSURLSession-backed HTTP client for macOS. NSURLSession uses the system TLS,
// proxy and trust stores and supports streaming uploads/downloads from files.
class MacHttpClient : public IHttpClient
{
public:
    HttpResponse PostJson(
        const std::string& url,
        const std::string& jsonBody,
        const std::string& bearerToken) override;

    HttpResponse PutFile(
        const std::string& url,
        const std::string& filePath,
        const std::map<std::string, std::string>& extraHeaders) override;

    HttpResponse Get(
        const std::string& url,
        const std::string& bearerToken) override;

    HttpResponse GetToFile(
        const std::string& url,
        const std::string& bearerToken,
        const std::string& filePath) override;
};
