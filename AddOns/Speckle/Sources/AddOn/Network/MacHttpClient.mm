#include "MacHttpClient.h"

#ifdef __APPLE__

#import <Foundation/Foundation.h>

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <stdexcept>

namespace
{
    NSString* ToNSString(const std::string& value)
    {
        return [[NSString alloc] initWithBytes:value.data()
                                         length:value.size()
                                       encoding:NSUTF8StringEncoding];
    }

    std::string ToString(NSString* value)
    {
        if (value == nil)
            return {};
        const char* utf8 = [value UTF8String];
        return utf8 != nullptr ? utf8 : "";
    }

    std::string ErrorMessage(NSError* error)
    {
        return error != nil ? ToString([error localizedDescription]) : "unknown macOS networking error";
    }

    NSMutableURLRequest* MakeRequest(const std::string& url, NSString* method, int timeoutSeconds = 600)
    {
        NSURL* nativeUrl = [NSURL URLWithString:ToNSString(url)];
        if (nativeUrl == nil)
            throw std::runtime_error("Invalid URL: " + url);

        NSMutableURLRequest* request = [NSMutableURLRequest requestWithURL:nativeUrl];
        [request setHTTPMethod:method];
        [request setTimeoutInterval:timeoutSeconds];
        return request;
    }

    NSURLSession* MakeSession(NSTimeInterval timeoutSeconds = 600.0)
    {
        NSURLSessionConfiguration* configuration = [NSURLSessionConfiguration ephemeralSessionConfiguration];
        configuration.timeoutIntervalForRequest = timeoutSeconds;
        configuration.timeoutIntervalForResource = timeoutSeconds;
        return [NSURLSession sessionWithConfiguration:configuration];
    }

    HttpResponse MakeResponse(NSURLResponse* nativeResponse, NSData* data)
    {
        NSHTTPURLResponse* httpResponse = [nativeResponse isKindOfClass:[NSHTTPURLResponse class]]
            ? static_cast<NSHTTPURLResponse*>(nativeResponse)
            : nil;
        if (httpResponse == nil)
            throw std::runtime_error("The server returned no HTTP response");

        HttpResponse response;
        response.statusCode = static_cast<int>(httpResponse.statusCode);
        if (data != nil && data.length > 0)
            response.body.assign(static_cast<const char*>(data.bytes), data.length);

        for (id key in httpResponse.allHeaderFields)
        {
            std::string name = ToString([key description]);
            std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c)
            {
                return static_cast<char>(std::tolower(c));
            });
            response.headers[name] = ToString([[httpResponse.allHeaderFields objectForKey:key] description]);
        }
        return response;
    }

    HttpResponse PerformDataRequest(NSMutableURLRequest* request)
    {
        __block NSData* responseData = nil;
        __block NSURLResponse* nativeResponse = nil;
        __block NSError* requestError = nil;
        dispatch_semaphore_t completed = dispatch_semaphore_create(0);
        NSURLSession* session = MakeSession(request.timeoutInterval);

        NSURLSessionDataTask* task = [session dataTaskWithRequest:request
            completionHandler:^(NSData* data, NSURLResponse* response, NSError* error)
            {
                responseData = data;
                nativeResponse = response;
                requestError = error;
                dispatch_semaphore_signal(completed);
            }];
        [task resume];
        dispatch_semaphore_wait(completed, DISPATCH_TIME_FOREVER);
        [session finishTasksAndInvalidate];

        if (requestError != nil)
            throw std::runtime_error("HTTP request failed: " + ErrorMessage(requestError));
        return MakeResponse(nativeResponse, responseData);
    }

    void SetBearerToken(NSMutableURLRequest* request, const std::string& bearerToken)
    {
        if (!bearerToken.empty())
            [request setValue:ToNSString("Bearer " + bearerToken) forHTTPHeaderField:@"Authorization"];
    }
}

HttpResponse MacHttpClient::PostJson(
    const std::string& url,
    const std::string& jsonBody,
    const std::string& bearerToken)
{
    @autoreleasepool
    {
        NSMutableURLRequest* request = MakeRequest(url, @"POST", postTimeoutSeconds);
        [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
        SetBearerToken(request, bearerToken);
        [request setHTTPBody:[NSData dataWithBytes:jsonBody.data() length:jsonBody.size()]];
        return PerformDataRequest(request);
    }
}

HttpResponse MacHttpClient::PutFile(
    const std::string& url,
    const std::string& filePath,
    const std::map<std::string, std::string>& extraHeaders,
    const UploadProgress& progress)
{
    @autoreleasepool
    {
        NSMutableURLRequest* request = MakeRequest(url, @"PUT");
        [request setValue:@"application/octet-stream" forHTTPHeaderField:@"Content-Type"];
        for (const auto& [name, value] : extraHeaders)
            [request setValue:ToNSString(value) forHTTPHeaderField:ToNSString(name)];

        NSURL* fileUrl = [NSURL fileURLWithPath:ToNSString(filePath)];
        __block NSData* responseData = nil;
        __block NSURLResponse* nativeResponse = nil;
        __block NSError* requestError = nil;
        dispatch_semaphore_t completed = dispatch_semaphore_create(0);
        NSURLSession* session = MakeSession();
        NSURLSessionUploadTask* task = [session uploadTaskWithRequest:request
            fromFile:fileUrl
            completionHandler:^(NSData* data, NSURLResponse* response, NSError* error)
            {
                responseData = data;
                nativeResponse = response;
                requestError = error;
                dispatch_semaphore_signal(completed);
            }];
        [task resume];

        // Poll from the calling thread (like WinHttpClient's chunk loop) so the
        // progress callback runs on the caller's thread and may throw to cancel.
        std::exception_ptr progressException = nullptr;
        std::int64_t lastReported = -1;
        while (dispatch_semaphore_wait(
                   completed, dispatch_time(DISPATCH_TIME_NOW, 100 * NSEC_PER_MSEC)) != 0)
        {
            if (progress == nullptr || progressException != nullptr)
                continue;

            const std::int64_t sent = task.countOfBytesSent;
            if (sent == lastReported)
                continue;
            lastReported = sent;

            try
            {
                progress(sent);
            }
            catch (...)
            {
                progressException = std::current_exception();
                [task cancel]; // completionHandler still fires (NSURLErrorCancelled)
            }
        }
        [session finishTasksAndInvalidate];

        if (progressException != nullptr)
            std::rethrow_exception(progressException);
        if (requestError != nil)
            throw std::runtime_error("File upload failed: " + ErrorMessage(requestError));
        return MakeResponse(nativeResponse, responseData);
    }
}

HttpResponse MacHttpClient::Get(const std::string& url, const std::string& bearerToken)
{
    @autoreleasepool
    {
        NSMutableURLRequest* request = MakeRequest(url, @"GET");
        SetBearerToken(request, bearerToken);
        return PerformDataRequest(request);
    }
}

HttpResponse MacHttpClient::GetToFile(
    const std::string& url,
    const std::string& bearerToken,
    const std::string& filePath)
{
    @autoreleasepool
    {
        NSMutableURLRequest* request = MakeRequest(url, @"GET");
        SetBearerToken(request, bearerToken);

        __block NSURLResponse* nativeResponse = nil;
        __block NSError* requestError = nil;
        __block NSError* fileError = nil;
        dispatch_semaphore_t completed = dispatch_semaphore_create(0);
        NSURLSession* session = MakeSession();
        NSURL* destination = [NSURL fileURLWithPath:ToNSString(filePath)];

        NSURLSessionDownloadTask* task = [session downloadTaskWithRequest:request
            completionHandler:^(NSURL* location, NSURLResponse* response, NSError* error)
            {
                nativeResponse = response;
                requestError = error;

                NSHTTPURLResponse* httpResponse = [response isKindOfClass:[NSHTTPURLResponse class]]
                    ? static_cast<NSHTTPURLResponse*>(response)
                    : nil;
                if (error == nil && location != nil && httpResponse.statusCode >= 200 && httpResponse.statusCode < 300)
                {
                    NSFileManager* files = [NSFileManager defaultManager];
                    [files removeItemAtURL:destination error:nil];
                    if (![files copyItemAtURL:location toURL:destination error:&fileError])
                        [files removeItemAtURL:destination error:nil];
                }
                dispatch_semaphore_signal(completed);
            }];
        [task resume];
        dispatch_semaphore_wait(completed, DISPATCH_TIME_FOREVER);
        [session finishTasksAndInvalidate];

        if (requestError != nil)
            throw std::runtime_error("File download failed: " + ErrorMessage(requestError));
        if (fileError != nil)
            throw std::runtime_error("Could not save downloaded file: " + ErrorMessage(fileError));

        HttpResponse response = MakeResponse(nativeResponse, nil);
        if (!response.IsSuccess())
            std::filesystem::remove(filePath);
        return response;
    }
}

#endif
