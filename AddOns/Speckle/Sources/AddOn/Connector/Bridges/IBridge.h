#pragma once
#include "RunMethodEventArgs.h"

class IBridge
{
public:
    virtual ~IBridge() = default;

    virtual void RunMethod(const RunMethodEventArgs& args) = 0;
};
