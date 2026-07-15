#include "AccountAuthenticator.h"

#ifdef __APPLE__

#include "HttpClientFactory.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <utility>
#include <vector>

namespace
{
    constexpr int CallbackPort = 29355;
    constexpr std::size_t MaximumRequestSize = 16 * 1024;
    constexpr auto AuthenticationTimeout = std::chrono::minutes(5);
    constexpr auto PollInterval = std::chrono::milliseconds(200);
    constexpr const char* AppId = "connectrV3";
    constexpr const char* AppSecret = "connectrV3";

    class Socket
    {
    public:
        explicit Socket(int descriptor = -1) : descriptor(descriptor) {}
        ~Socket()
        {
            if (descriptor >= 0)
                close(descriptor);
        }

        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        Socket(Socket&& other) noexcept : descriptor(std::exchange(other.descriptor, -1)) {}
        Socket& operator=(Socket&& other) noexcept
        {
            if (this != &other)
            {
                if (descriptor >= 0)
                    close(descriptor);
                descriptor = std::exchange(other.descriptor, -1);
            }
            return *this;
        }

        int Get() const { return descriptor; }

    private:
        int descriptor;
    };

    Socket CreateIpv4CallbackListener()
    {
        Socket listener(socket(AF_INET, SOCK_STREAM, 0));
        if (listener.Get() < 0)
            throw std::runtime_error("Could not create the authentication callback listener");

        int reuseAddress = 1;
        setsockopt(
            listener.Get(),
            SOL_SOCKET,
            SO_REUSEADDR,
            &reuseAddress,
            sizeof(reuseAddress));

        sockaddr_in address = {};
        address.sin_family = AF_INET;
        address.sin_port = htons(CallbackPort);
        address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        if (bind(
                listener.Get(),
                reinterpret_cast<const sockaddr*>(&address),
                sizeof(address)) != 0)
            throw std::runtime_error(
                "Could not listen for the Speckle authentication callback on localhost:29355: " +
                std::string(std::strerror(errno)));
        if (listen(listener.Get(), 1) != 0)
            throw std::runtime_error("Could not start the authentication callback listener");

        return listener;
    }

    Socket CreateIpv6CallbackListener()
    {
        Socket listener(socket(AF_INET6, SOCK_STREAM, 0));
        if (listener.Get() < 0)
            throw std::runtime_error("Could not create the IPv6 authentication callback listener");

        int reuseAddress = 1;
        int ipv6Only = 1;
        setsockopt(
            listener.Get(),
            SOL_SOCKET,
            SO_REUSEADDR,
            &reuseAddress,
            sizeof(reuseAddress));
        setsockopt(
            listener.Get(),
            IPPROTO_IPV6,
            IPV6_V6ONLY,
            &ipv6Only,
            sizeof(ipv6Only));

        sockaddr_in6 address = {};
        address.sin6_family = AF_INET6;
        address.sin6_port = htons(CallbackPort);
        address.sin6_addr = in6addr_loopback;
        if (bind(
                listener.Get(),
                reinterpret_cast<const sockaddr*>(&address),
                sizeof(address)) != 0 ||
            listen(listener.Get(), 1) != 0)
            throw std::runtime_error("Could not start the IPv6 authentication callback listener");

        return listener;
    }

    std::vector<Socket> CreateCallbackListeners()
    {
        std::vector<Socket> listeners;
        listeners.push_back(CreateIpv4CallbackListener());
        try
        {
            listeners.push_back(CreateIpv6CallbackListener());
        }
        catch (...)
        {
            // IPv4 localhost remains available on systems without IPv6.
        }
        return listeners;
    }

    void SendAll(int socketDescriptor, const std::string& response)
    {
        std::size_t sent = 0;
        while (sent < response.size())
        {
            const ssize_t count = send(
                socketDescriptor,
                response.data() + sent,
                response.size() - sent,
                0);
            if (count <= 0)
                return;
            sent += static_cast<std::size_t>(count);
        }
    }

    void SendBrowserResponse(
        int socketDescriptor,
        const std::string& title,
        const std::string& message)
    {
        const std::string body =
            "<!doctype html><html><head><meta charset=\"utf-8\">"
            "<title>Speckle authentication</title></head>"
            "<body style=\"background:#fafafa;font-family:Inter,Roboto,sans-serif;"
            "text-align:center;padding:48px\"><h1>" + title +
            "</h1><p>" + message + "</p></body></html>";
        const std::string response =
            "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n"
            "Cache-Control: no-store\r\nConnection: close\r\nContent-Length: " +
            std::to_string(body.size()) + "\r\n\r\n" + body;
        SendAll(socketDescriptor, response);
    }

    std::string ReadHttpRequest(int socketDescriptor, std::stop_token stopToken)
    {
        std::string request;
        request.reserve(2048);
        char buffer[2048];
        while (!stopToken.stop_requested() && request.size() < MaximumRequestSize)
        {
            pollfd descriptor = { socketDescriptor, POLLIN, 0 };
            const int pollResult = poll(
                &descriptor,
                1,
                static_cast<int>(PollInterval.count()));
            if (pollResult < 0)
                throw std::runtime_error("The authentication callback listener failed");
            if (pollResult == 0)
                continue;

            const ssize_t count = recv(socketDescriptor, buffer, sizeof(buffer), 0);
            if (count <= 0)
                break;
            request.append(buffer, static_cast<std::size_t>(count));
            if (request.find("\r\n\r\n") != std::string::npos)
                return request;
        }

        if (stopToken.stop_requested())
            throw std::runtime_error("Authentication was cancelled");
        throw std::runtime_error("The authentication callback request was invalid");
    }

    std::string WaitForAccessCode(
        std::vector<Socket>& listeners,
        std::stop_token stopToken)
    {
        const auto deadline = std::chrono::steady_clock::now() + AuthenticationTimeout;
        while (!stopToken.stop_requested() && std::chrono::steady_clock::now() < deadline)
        {
            std::vector<pollfd> descriptors;
            descriptors.reserve(listeners.size());
            for (const Socket& listener : listeners)
                descriptors.push_back({ listener.Get(), POLLIN, 0 });
            const int pollResult = poll(
                descriptors.data(),
                static_cast<nfds_t>(descriptors.size()),
                static_cast<int>(PollInterval.count()));
            if (pollResult < 0)
                throw std::runtime_error("The authentication callback listener failed");
            if (pollResult == 0)
                continue;

            std::size_t readyListener = 0;
            while (readyListener < descriptors.size() &&
                   (descriptors[readyListener].revents & POLLIN) == 0)
                ++readyListener;
            if (readyListener == descriptors.size())
                continue;

            sockaddr_storage clientAddress = {};
            socklen_t clientAddressLength = sizeof(clientAddress);
            Socket client(accept(
                listeners[readyListener].Get(),
                reinterpret_cast<sockaddr*>(&clientAddress),
                &clientAddressLength));
            if (client.Get() < 0)
                continue;

            int noSigPipe = 1;
            setsockopt(
                client.Get(),
                SOL_SOCKET,
                SO_NOSIGPIPE,
                &noSigPipe,
                sizeof(noSigPipe));
            try
            {
                const std::string accessCode =
                    AccountAuthentication::ExtractAccessCodeFromHttpRequest(
                        ReadHttpRequest(client.Get(), stopToken));
                SendBrowserResponse(
                    client.Get(),
                    "Success!",
                    "Your Speckle Connector is now authorized. You may close this window.");
                return accessCode;
            }
            catch (const std::exception&)
            {
                SendBrowserResponse(
                    client.Get(),
                    "Authentication failed",
                    "Return to the Speckle Connector and try again.");
                throw;
            }
        }

        if (stopToken.stop_requested())
            throw std::runtime_error("Authentication was cancelled");
        throw std::runtime_error("Authentication timed out");
    }

    void RequireSuccess(const HttpResponse& response, const std::string& operation)
    {
        if (!response.IsSuccess())
            throw std::runtime_error(
                operation + " failed with HTTP status " +
                std::to_string(response.statusCode));
    }
}

nlohmann::json AccountAuthentication::Authenticate(
    const std::string& rawServerUrl,
    std::stop_token stopToken,
    const BrowserOpener& openBrowser)
{
    const std::string serverUrl = AccountAuthentication::NormalizeServerUrl(rawServerUrl);
    auto httpClient = CreateHttpClient();

    const HttpResponse capabilityResponse =
        httpClient->Get(serverUrl + "/oauth/token", {});
    const bool useModernOAuth = capabilityResponse.statusCode == 200;

    const std::string codeVerifier = GenerateCodeVerifier();
    const std::string codeChallenge = useModernOAuth
        ? GenerateCodeChallenge(codeVerifier)
        : codeVerifier;
    const std::string authorizationUrl =
        serverUrl + "/authn/verify/" + AppId + "/" + codeChallenge +
        (useModernOAuth ? "?code_challenge_method=S256" : "");
    const std::string tokenUrl = serverUrl +
        (useModernOAuth ? "/oauth/token" : "/auth/token");

    std::vector<Socket> listeners = CreateCallbackListeners();
    if (stopToken.stop_requested())
        throw std::runtime_error("Authentication was cancelled");
    openBrowser(authorizationUrl);
    const std::string accessCode = WaitForAccessCode(listeners, stopToken);

    nlohmann::json tokenRequest = {
        { "appId", AppId },
        { "accessCode", accessCode }
    };
    if (useModernOAuth)
        tokenRequest["codeVerifier"] = codeVerifier;
    else
    {
        tokenRequest["appSecret"] = AppSecret;
        tokenRequest["challenge"] = codeVerifier;
    }

    const HttpResponse tokenResponse =
        httpClient->PostJson(tokenUrl, tokenRequest.dump(), {});
    RequireSuccess(tokenResponse, "Speckle token exchange");
    const nlohmann::json tokenData = nlohmann::json::parse(tokenResponse.body);
    if (!tokenData.contains("token") || !tokenData["token"].is_string() ||
        tokenData["token"].get<std::string>().empty())
        throw std::runtime_error("The Speckle token response was incomplete");

    const std::string token = tokenData["token"].get<std::string>();
    const std::string refreshToken =
        tokenData.contains("refreshToken") && tokenData["refreshToken"].is_string()
            ? tokenData["refreshToken"].get<std::string>()
            : std::string{};
    const nlohmann::json graphQlRequest = {
        { "query", R"(
            query {
                activeUser { id name email company avatar }
                serverInfo {
                    name company description version
                    migration { movedFrom movedTo }
                }
            }
        )" }
    };
    const HttpResponse userInfoResponse = httpClient->PostJson(
        serverUrl + "/graphql",
        graphQlRequest.dump(),
        token);
    RequireSuccess(userInfoResponse, "Speckle account information request");

    return BuildAccount(
        serverUrl,
        token,
        refreshToken,
        nlohmann::json::parse(userInfoResponse.body),
        false);
}

#else

nlohmann::json AccountAuthentication::Authenticate(
    const std::string&,
    std::stop_token,
    const BrowserOpener&)
{
    throw std::runtime_error(
        "Native Speckle account authentication is not supported on this platform");
}

#endif
