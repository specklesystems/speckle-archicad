#include "UrlLauncher.h"

#include "DefaultProgramRunner.hpp"
#include "UniString.hpp"

#include <stdexcept>

void UrlLauncher::OpenInDefaultBrowser(const std::string& url)
{
    if (!OSUtils::OpenWithDefaultBrowser(GS::UniString(url.c_str(), CC_UTF8)))
        throw std::runtime_error("Could not open the URL in the default browser");
}
