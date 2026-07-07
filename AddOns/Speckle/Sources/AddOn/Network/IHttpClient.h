#pragma once

#include <map>
#include <string>

// Minimal HTTP surface for the Speckle 4.0 artefact upload path:
// one JSON POST (GraphQL + the v2 sign/complete endpoints) and one
// streamed file PUT (presigned S3 upload). Implemented with WinHTTP on
// Windows (no vendored TLS); add a libcurl implementation when the mac
// build becomes real.
struct HttpResponse
{
    int statusCode = 0;
    std::string body;
    std::map<std::string, std::string> headers; // lowercase keys

    bool IsSuccess() const { return statusCode >= 200 && statusCode < 300; }
};

class IHttpClient
{
public:
    virtual ~IHttpClient() = default;

    // POST a JSON body to an absolute https URL. bearerToken may be empty (presigned endpoints).
    virtual HttpResponse PostJson(
        const std::string& url,
        const std::string& jsonBody,
        const std::string& bearerToken) = 0;

    // PUT a local file to an absolute https URL (presigned S3), streaming from disk.
    // extraHeaders come from the sign response's additionalRequestHeaders.
    virtual HttpResponse PutFile(
        const std::string& url,
        const std::string& filePath,
        const std::map<std::string, std::string>& extraHeaders) = 0;
};
