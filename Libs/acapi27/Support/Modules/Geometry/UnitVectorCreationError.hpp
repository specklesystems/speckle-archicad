#ifndef UNITVECTORCREATIONERROR_HPP
#define UNITVECTORCREATIONERROR_HPP
#pragma once

#include "GeometricDefinitions.h"

namespace Geometry {

class GEOMETRY_DLL_EXPORT UnitVectorCreationError : public GeometryException
{
public:
	virtual ~UnitVectorCreationError ();
};

}

#endif