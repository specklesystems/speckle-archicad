#pragma once
#include "ArchiCadApiException.h"

#ifndef CHECK_ERROR
#define CHECK_ERROR(f) { GSErrCode err = (f); if (err != NoError) { throw ArchiCadApiException(err); } }
#endif