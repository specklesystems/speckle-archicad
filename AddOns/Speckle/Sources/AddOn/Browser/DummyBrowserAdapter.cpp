#include "DummyBrowserAdapter.h"
#include "Binding.h"
#include "RunMethodEventArgs.h"
#include "JsonFileWriter.h"

DummyBrowserAdapter::DummyBrowserAdapter(){}

void DummyBrowserAdapter::RegisterBinding(Binding* /*binding*/)
{
}

void DummyBrowserAdapter::ExecuteJS(const std::string& /*command*/)
{
}

void DummyBrowserAdapter::LoadURL(const std::string& /*url*/)
{
}
