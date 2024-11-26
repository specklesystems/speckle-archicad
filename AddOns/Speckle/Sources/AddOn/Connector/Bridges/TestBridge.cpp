#include "TestBridge.h"
#include "LoggerFactory.h"

TestBridge::TestBridge(IBrowserAdapter* browser)
{
    Init(browser);
}

void TestBridge::Init(IBrowserAdapter* browser)
{
    testBinding = std::make_unique<Binding>(
        "testBinding",
        std::vector<std::string>{ "GetComplexType", "GoAway", "SayHi", "TriggerEvent" },
        browser);

    testBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void TestBridge::OnRunMethod(const RunMethodEventArgs& args)
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
        GET_LOGGER("TestBridge")->Info("Invalid method name");
    }
}

void TestBridge::GetComplexType(const RunMethodEventArgs& args)
{
    GET_LOGGER("TestBridge")->Info(args.methodName + " called");
}

void TestBridge::GoAway(const RunMethodEventArgs& args)
{
    GET_LOGGER("TestBridge")->Info(args.methodName + " called");
}

void TestBridge::SayHi(const RunMethodEventArgs& args)
{
    GET_LOGGER("TestBridge")->Info(args.methodName + " called");
}

void TestBridge::TriggerEvent(const RunMethodEventArgs& args)
{
    GET_LOGGER("TestBridge")->Info(args.methodName + " called");
}
