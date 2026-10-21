// *********************************************************************************************************************
// Functions and structures for model memory consumption reports.
// *********************************************************************************************************************

#if !defined (MODEL3DSIZEREPORT_CPP)
#define MODEL3DSIZEREPORT_CPP

#pragma once

#include "UniString.hpp"
#include "PagedArray.hpp"

#include "Model3D/Model3DExport.h"


namespace GS {
	class OChannel;
}

namespace Modeler {

class ContainerSizeReport;
class CompositeContainerSizeReport;

// =====================================================================================================================
// Report classes
// =====================================================================================================================

enum SizeReportType { LogicalSizeReport, ActualSizeReport };

struct ModelElementCounts
{
	UInt64 elemCount;
	UInt64 elemBodyBoundsCount;
	UInt64 hotspotCount;
	UInt64 lightSourceCount;
	UInt64 baseElemCount;
	UInt64 meshBodyCount;
	UInt64 meshBodyPolygonCount;
	UInt64 meshBodyConvexPolygonCount;
	UInt64 meshBodyPolygonNormalCount;
	UInt64 meshBodyPolygonEdgeCount;
	UInt64 meshBodyEdgeCount;
	UInt64 meshBodyVertexCount;
	UInt64 nurbsBodyCount;
	UInt64 nurbsBodyVertexCount;
	UInt64 nurbsBodyEdgeCount;
	UInt64 nurbsBodyTrimCount;
	UInt64 nurbsBodyLoopCount;
	UInt64 nurbsBodyFaceCount;
	UInt64 nurbsBodyShellCount;
	UInt64 nurbsBodyLumpCount;
	UInt64 nurbsBodyCurve2DCount;
	UInt64 nurbsBodyCurve3DCount;
	UInt64 nurbsBodySurfaceCount;

	ModelElementCounts ()
		: elemCount (0)
		, elemBodyBoundsCount (0)
		, hotspotCount (0)
		, lightSourceCount (0)
		, baseElemCount (0)
		, meshBodyCount (0)
		, meshBodyPolygonCount (0)
		, meshBodyConvexPolygonCount (0)
		, meshBodyPolygonNormalCount (0)
		, meshBodyPolygonEdgeCount (0)
		, meshBodyEdgeCount (0)
		, meshBodyVertexCount (0)
		, nurbsBodyCount (0)
		, nurbsBodyVertexCount (0)
		, nurbsBodyEdgeCount (0)
		, nurbsBodyTrimCount (0)
		, nurbsBodyLoopCount (0)
		, nurbsBodyFaceCount (0)
		, nurbsBodyShellCount (0)
		, nurbsBodyLumpCount (0)
		, nurbsBodyCurve2DCount (0)
		, nurbsBodyCurve3DCount (0)
		, nurbsBodySurfaceCount (0)
	{ /* do nothing */ }
};

// ---------------------------------------------------------------------------------------------------------------------
// Report of a single container of elements.
// ---------------------------------------------------------------------------------------------------------------------
class MODEL3D_DLL_EXPORT ContainerSizeReport
{
	friend class CompositeContainerSizeReport;	// direct access for merging

private:
	GS::UniString name;

	UInt64 elementSize;
	UInt64 usedCount;		// element count actually allocated in memory
	UInt64 overheadBytes;

public:
	ContainerSizeReport (const GS::UniString& nameIn, UInt64 elementSizeIn, UInt64 usedCountIn, UInt64 overheadBytesIn = 0)
		: name (nameIn)
		, elementSize (elementSizeIn)
		, usedCount (usedCountIn)
		, overheadBytes (overheadBytesIn)
	{ /* do nothing */ }

	const GS::UniString& GetName () const {
		return name;
	}

	UInt64 GetElementSize () const {
		return elementSize;
	}

	UInt64 GetElementCount () const {
		return usedCount;
	}

	UInt64 GetOverheadBytes () const {
		return overheadBytes;
	}

	UInt64 GetUsedBytes () const {
		return overheadBytes + elementSize * usedCount;
	}
};


// ---------------------------------------------------------------------------------------------------------------------
// Report of a group of containers.
// ---------------------------------------------------------------------------------------------------------------------
class MODEL3D_DLL_EXPORT CompositeContainerSizeReport
{
private:
	GS::UniString name;
	UInt64 overheadBytes;		// overhead for this level (i.e. non-cumulative)

	GS::PagedArray<ContainerSizeReport>				directContainerReports;
	GS::PagedArray<CompositeContainerSizeReport>	lowerLevelReports;

public:
	CompositeContainerSizeReport (const GS::UniString& nameIn, UInt64 overheadBytesIn = 0)
		: name (nameIn)
		, overheadBytes (overheadBytesIn)
	{ /* do nothing */ }

	CompositeContainerSizeReport& AddContainerReport	(const ContainerSizeReport& container);
	CompositeContainerSizeReport& AddLowerLevelReport	(const CompositeContainerSizeReport& lowerLevel);
	CompositeContainerSizeReport& CombineWithReport		(const CompositeContainerSizeReport& other);

	UInt64 GetElementCount () const;
	UInt64 GetOverheadBytes () const;
	UInt64 GetUsedBytes () const;

	void Print (GS::OChannel& oc, UInt64 printLowerLevels = GS::MaxUInt64) const;
};


template <class ContainerT>
ContainerSizeReport	ReportContainer (const GS::UniString& containerName, const ContainerT& container)
{
	return ContainerSizeReport (containerName, sizeof(typename ContainerT::ValueType), container.GetSize ());
}

}	// namespace Modeler

#endif // MODEL3DSIZEREPORT_CPP