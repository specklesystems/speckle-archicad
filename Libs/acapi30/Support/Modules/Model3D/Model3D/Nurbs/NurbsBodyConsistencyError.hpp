#ifndef NURBSBODYCONSISTENCYERROR_HPP
#define NURBSBODYCONSISTENCYERROR_HPP

#pragma once

// from GSRoot
#include "GSException.hpp"

#include "Model3D/Model3DExport.h"

namespace Modeler {

enum class NurbsBodyConsistencyError {
	InvalidPen,
	InvalidMaterial,
	InvalidNurbsLibData
};

class MODEL3D_DLL_EXPORT NurbsBodyConsistencyException : public GS::Exception {
	NurbsBodyConsistencyError error;
public:
	NurbsBodyConsistencyException (NurbsBodyConsistencyError error) : error (error) {}
	virtual ~NurbsBodyConsistencyException ();

	const NurbsBodyConsistencyError& GetError () const { return error; }
};

} //namespace Modeler

#endif // NURBSBODYCONSISTENCYERROR_HPP