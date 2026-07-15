#include "AccountAuthenticator.h"
#include "HttpClientFactory.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>

namespace
{
    class FakeHttpClient final : public IHttpClient
    {
    public:
        HttpResponse Get(const std::string& url, const std::string&) override
        {
            assert(url == "http://127.0.0.1:3000/oauth/token");
            return { 200, "supported", {} };
        }

        HttpResponse PostJson(
            const std::string& url,
            const std::string& jsonBody,
            const std::string& bearerToken) override
        {
            const auto body = nlohmann::json::parse(jsonBody);
            if (url.ends_with("/oauth/token"))
            {
                assert(bearerToken.empty());
                assert(body["appId"] == "connectrV3");
                assert(body["accessCode"] == "test-access-code");
                assert(body["codeVerifier"].is_string());
                return {
                    200,
                    R"({"token":"test-access-token","refreshToken":"test-refresh-token"})",
                    {}
                };
            }

            assert(url == "http://127.0.0.1:3000/graphql");
            assert(bearerToken == "test-access-token");
            assert(body["query"].get<std::string>().find("activeUser") != std::string::npos);
            return {
                200,
                R"({"data":{"activeUser":{"id":"user-id","name":"Test User","email":"test@example.com"},"serverInfo":{"name":"Test Server","version":"test"}}})",
                {}
            };
        }

        HttpResponse PutFile(
            const std::string&,
            const std::string&,
            const std::map<std::string, std::string>&) override
        {
            throw std::logic_error("Not used by account authentication");
        }

        HttpResponse GetToFile(
            const std::string&,
            const std::string&,
            const std::string&) override
        {
            throw std::logic_error("Not used by account authentication");
        }
    };

    void SendCallbackRequest()
    {
        const int descriptor = socket(AF_INET, SOCK_STREAM, 0);
        assert(descriptor >= 0);

        sockaddr_in address = {};
        address.sin_family = AF_INET;
        address.sin_port = htons(29355);
        address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        assert(connect(
            descriptor,
            reinterpret_cast<const sockaddr*>(&address),
            sizeof(address)) == 0);

        const std::string request =
            "GET /?access_code=test-access-code HTTP/1.1\r\n"
            "Host: localhost:29355\r\nConnection: close\r\n\r\n";
        assert(send(descriptor, request.data(), request.size(), 0) ==
            static_cast<ssize_t>(request.size()));

        std::string response;
        char buffer[1024];
        ssize_t count = 0;
        while ((count = recv(descriptor, buffer, sizeof(buffer), 0)) > 0)
            response.append(buffer, static_cast<std::size_t>(count));
        close(descriptor);

        assert(response.starts_with("HTTP/1.1 200 OK"));
        assert(response.find("Success!") != std::string::npos);
    }
}

std::shared_ptr<IHttpClient> CreateHttpClient()
{
    return std::make_shared<FakeHttpClient>();
}

int main()
{
    std::thread callbackThread;
    std::string authorizationUrl;
    const auto account = AccountAuthentication::Authenticate(
        "http://127.0.0.1:3000/",
        {},
        [&](const std::string& url)
        {
            authorizationUrl = url;
            callbackThread = std::thread(SendCallbackRequest);
        });
    callbackThread.join();

    assert(authorizationUrl.starts_with(
        "http://127.0.0.1:3000/authn/verify/connectrV3/"));
    assert(authorizationUrl.ends_with("?code_challenge_method=S256"));
    assert(account["token"] == "test-access-token");
    assert(account["refreshToken"] == "test-refresh-token");
    assert(account["serverInfo"]["url"] == "http://127.0.0.1:3000");
    assert(account["userInfo"]["id"] == "user-id");
    return 0;
}
