#include "TestBridge.h"
#include "InvalidMethodNameException.h"
#include "ArchiCadApiException.h"
#include "ErrorReport.h"


TestBridge::TestBridge(IBrowserAdapter* browser)
{
    testBinding = std::make_unique<Binding>(
        "testBinding",
        std::vector<std::string>{ "GetComplexType", "GoAway", "SayHi", "TriggerEvent" },
        browser);

    testBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

// POC duplicated code, move try catch logic to Binding
void TestBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const ArchiCadApiException& acex)
    {
        testBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured in the ArchiCAD API" , acex.what(), false });
    }
    catch (const std::exception& stdex)
    {
        testBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Exception occured" , stdex.what(), false });
    }
    catch (...)
    {
        testBinding->SetToastNotification(
            ToastNotification{ ToastNotificationType::DANGER , "Unknown exception occured" , "", false });
    }
}

void TestBridge::RunMethod(const RunMethodEventArgs& args)
{
    if (args.methodName == "GetComplexType")
    {
        GetComplexType(args);
    }
    else if (args.methodName == "GoAway")
    {
        GoAway(args);
    }
    else if (args.methodName == "SayHi")
    {
        SayHi(args);
    }
    else if (args.methodName == "TriggerEvent")
    {
        TriggerEvent(args);
    }
    else
    {
        throw InvalidMethodNameException(args.methodName);
    }
}

void TestBridge::GetComplexType(const RunMethodEventArgs& args)
{
    nlohmann::json j;
    j["id"] = "1234";
    j["count"] = 1234;
    args.eventSource->SetResult(args.methodId, j);
}

void TestBridge::GoAway(const RunMethodEventArgs& args)
{
    args.eventSource->SetResult(args.methodId, nullptr);
}

void TestBridge::SayHi(const RunMethodEventArgs& args)
{
    if (args.data.size() < 3)
    {
        ErrorReport err{};
        err.error = "Problem";
        err.message = "No good";
        args.eventSource->SetResult(args.methodId, err);
        return;
    }

    bool sayHelloNotHi = false;
    if (args.data.size() == 3)
        sayHelloNotHi = args.data[2].get<bool>();

    std::string name = args.data[0].get<std::string>();
    int count = args.data[1].get<int>();

    std::string baseGreeting{ (sayHelloNotHi ? "Hello" : "Hi") + name + "!\n" };
    
    std::string finalGreeting = "";

    for (auto i = count; i--; )
        finalGreeting += baseGreeting;

    if (finalGreeting.empty())
        finalGreeting = baseGreeting;

    args.eventSource->SetResult(args.methodId, finalGreeting);
}

void TestBridge::TriggerEvent(const RunMethodEventArgs& args)
{
    if (args.data.size() < 1)
        throw std::invalid_argument("Too few of arguments when calling " + args.methodName);

    std::string eventName = args.data[0].get<std::string>();
    if (eventName == "emptyTestEvent")
    {
        args.eventSource->Emit(eventName);
        args.eventSource->ResponseReady(args.methodId);
    }
    else if (eventName == "testEvent")
    {
        nlohmann::json j;
        j["count"] = 42;
        j["name"] = "foo";
        j["isOK"] = true;
        args.eventSource->Send(eventName, j);
    }
}
