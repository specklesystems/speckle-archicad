#if !defined (POLYGONKDTREE_HPP)
#define POLYGONKDTREE_HPP

#pragma once

#include "Definitions.hpp"

#include "Model3DPrivExp.h"

namespace Modeler {
	class Elem;
	class Model3DViewer;
}

namespace Modeler {

struct	MODEL3D_PRIVATE_EXPORT PolygonModelReferences {
	const Modeler::Elem*	elemPtr;
	UIndex					bodyIdx;
	UIndex					pgonIdx;

	PolygonModelReferences ()
		: elemPtr (nullptr)
		, bodyIdx (0)
		, pgonIdx (0)
	{
		// do nothing
	}

	PolygonModelReferences (const Modeler::Elem* elemPtr, UIndex bodyIdx, UIndex pgonIdx)
		: elemPtr (elemPtr)
		, bodyIdx (bodyIdx)
		, pgonIdx (pgonIdx)
	{
		// do nothing
	}

	bool	operator == (const PolygonModelReferences& rhs) const	{ return elemPtr == rhs.elemPtr && bodyIdx == rhs.bodyIdx && pgonIdx == rhs.pgonIdx; }
	bool	operator != (const PolygonModelReferences& rhs) const	{ return !operator == (rhs); }

	ULong	GenerateHashValue () const;

	Int32 GetElemIdx (const Modeler::Model3DViewer& modelViewer) const;
};

}	// namespace Modeler

#endif	// POLYGONKDTREE_HPP
