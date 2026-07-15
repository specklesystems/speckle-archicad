#pragma once

#include <memory>

#include "IHttpClient.h"

std::shared_ptr<IHttpClient> CreateHttpClient();
