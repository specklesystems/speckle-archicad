#include "TestBridge.h"
#include "InvalidMethodNameException.h"


TestBridge::TestBridge(IBrowserAdapter* browser)
{
    testBinding = std::make_unique<Binding>(
        "testBinding",
        std::vector<std::string>{ "GetComplexType", "GoAway", "SayHi", "TriggerEvent" },
        browser);

    testBinding->RunMethodRequested += [this](const RunMethodEventArgs& args) { OnRunMethod(args); };
}

void TestBridge::OnRunMethod(const RunMethodEventArgs& args)
{
    try
    {
        RunMethod(args);
    }
    catch (const std::exception& e)
    {
        // TODO: pass message to browser
        std::string msg = e.what();
        std::cout << msg;
    }
    catch (...)
    {
        // no good
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

void TestBridge::GetComplexType(const RunMethodEventArgs& /*args*/)
{
    // TODO implement
}

void TestBridge::GoAway(const RunMethodEventArgs& /*args*/)
{
    // TODO implement
}

void TestBridge::SayHi(const RunMethodEventArgs& /*args*/)
{
    // TODO implement
}

void TestBridge::TriggerEvent(const RunMethodEventArgs& /*args*/)
{
    // TODO implement
}
