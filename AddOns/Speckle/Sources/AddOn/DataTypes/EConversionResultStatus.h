#pragma once

enum class ConversionResultStatus
{
    CONVERSION_NONE = 0, // Do not use
    CONVERSION_SUCCESS = 1,
    CONVERSION_INFO = 2, // Not in use yet, maybe later as discussed
    CONVERSION_WARNING = 3, // Not in use yet, maybe later as discussed
    CONVERSION_ERROR = 4
};
