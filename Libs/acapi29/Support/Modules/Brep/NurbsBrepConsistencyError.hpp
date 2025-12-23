// *********************************************************************************************************************
// Exception type for errors during NURBS BRep building and consistency check
// *********************************************************************************************************************

#if !defined(NURBSCONSYSTENCYERROR_HPP)
#define NURBSCONSYSTENCYERROR_HPP

#pragma once

#include "BrepExport.hpp"

namespace Brep {

// Order and value matters because of corresponding error strings in STRSConv.grc (ERROR_STRS)
class NurbsBrepConsistencyError {
public:
	enum class Code {
		/* 1*/	TrimOverloaded = 1,			// too many loops attached (more than 1)
		/* 2*/	LoopOverloaded,				// too many faces attached (more than 1)
		/* 3*/	FaceOverloaded,				// too many shells attached (more than 1)
		/* 4*/	ShellOverloaded,			// too many lumps attached (more than 1)
		/* 5*/	InvalidVertexIndexInEdge,
		/* 6*/	InvalidTrimIndexInEdge,		// "backreferece" error
		/* 7*/	InvalidVertexIndexInTrim,
		/* 8*/	InvalidEdgeIndexInTrim,
		/* 9*/	InvalidLoopIndexInTrim,		// "backreferece" error
		/*10*/	InvalidTrimIndexInLoop,
		/*11*/	InvalidFaceIndexInLoop,		// "backreferece" error
		/*12*/	InvalidLoopIndexInFace,
		/*13*/	InvalidShellIndexInFace,	// "backreferece" error
		/*14*/	InvalidFaceIndexInShell,
		/*15*/	InvalidLumpIndexInShell,	// "backreferece" error
		/*16*/	InvalidShellIndexInLump,
		/*17*/	InvalidCurve2DIndex,
		/*18*/	InvalidCurve3DIndex,
		/*19*/	InvalidSurfaceIndex,
		/*20*/	EmptyTrimList,				// no trim given for loop
		/*21*/	EmptyLoopList,				// no loop given for face
		/*22*/	EmptyFaceList,				// no face given for shell
		/*23*/	EmptyShellList,				// no shell given for lump
		/*24*/	Curve2DInvalidDouble,		// invalid floating point values (NaN or Infinite)
		/*25*/	Curve3DInvalidDouble,
		/*26*/	SurfaceInvalidDouble,
		/*27*/	VertexInvalidDouble,
		/*28*/	EdgeInvalidDouble,
		/*29*/	TrimInvalidDouble,
		/*30*/	FaceInvalidDouble,
		/*31*/	InvalidCurve2DParameter,	// 2D curve description is invalid or empty
		/*32*/	InvalidCurve3DParameter,	// 3D curve description is invalid or empty
		/*33*/	InvalidSurfaceParameter,	// surface description is invalid or empty
		/*34*/	WrongCurve2DSubDomain,		// 2D curve parameters out of range or swapped or identical
		/*35*/	WrongCurve3DSubDomain,		// 3D curve parameters out of range or swapped or identical
		/*36*/	RingEdgeNotClosedCurve,		// curve of ring edge is not closed geometrically
		/*37*/	EdgeAndVertexNotFit,		// edge curve endpoints does not properly coincide with the vertices of edge
		/*38*/	LoopDegenerated,			// loop has a zero extent geometrically
		/*39*/	LoopNotContinuous,			// subsequent elements of loop are not connected topologically
		/*40*/	EdgeEndpointsNotFit,		// subsequent edge curve endpoints in a loop does not coincide geometrically
		/*41*/	TrimEndpointsNotFit,		// endpoints of subsequent trims in a loop does not coincide in the 2D parameter space
		/*42*/	FaceTrimmingCurveNotFit,	// a trimming curve of the face does not fit in the domain of the face
		/*43*/	FaceTrimAndEdgeNotFit,		// boundary of trimmed face does not coincide with the corresponding edge
		/*44*/	FaceTrimAndVertexNotFit,	// boundary of trimmed face does not coincide with the corresponding vertex
		/*45*/	ShellNotClosed,				// shell has boundary edge
		/*46*/	ShellNotConnected,			// shell consist of multiple disjunct part
		/*47*/	EdgeInvalidState,
		/*48*/	TrimInvalidState
	};

	static const Int64 InvalidPrimitiveIndex = -MaxInt64;

private:
	Code	code;
	Int64	badPrimitiveIndex1;
	Int64	badPrimitiveIndex2;
	Int64	badPrimitiveIndex3;

public:

	NurbsBrepConsistencyError (Code code, Int64 badPrimitiveIndex1 = InvalidPrimitiveIndex, Int64 badPrimitiveIndex2 = InvalidPrimitiveIndex, Int64 badPrimitiveIndex3 = InvalidPrimitiveIndex) :
		code (code),
		badPrimitiveIndex1 (badPrimitiveIndex1),
		badPrimitiveIndex2 (badPrimitiveIndex2),
		badPrimitiveIndex3 (badPrimitiveIndex3)
	{
		DBASSERT (badPrimitiveIndex1 != InvalidPrimitiveIndex || badPrimitiveIndex2 == InvalidPrimitiveIndex);
		DBASSERT (badPrimitiveIndex2 != InvalidPrimitiveIndex || badPrimitiveIndex3 == InvalidPrimitiveIndex);
	}

	Code	GetCode ()				const { return code; }
	Int64	GetBadPrimitiveGDLIndex1 () const { return badPrimitiveIndex1 + 1; }
	Int64	GetBadPrimitiveGDLIndex2 () const { return badPrimitiveIndex2 + 1; }
	Int64	GetBadPrimitiveGDLIndex3 () const { return badPrimitiveIndex3 + 1; }

	UInt32	GetBadPrimitiveCount () const
	{
		if (badPrimitiveIndex1 == InvalidPrimitiveIndex) {
			return 0;
		} else if (badPrimitiveIndex2 == InvalidPrimitiveIndex) {
			return 1;
		} else if (badPrimitiveIndex3 == InvalidPrimitiveIndex) {
			return 2;
		} else {
			return 3;
		}
	}

};

class BREP_DLL_EXPORT NurbsBrepConsistencyException: public GS::Exception
{
public:
	NurbsBrepConsistencyException (const NurbsBrepConsistencyError& error);
	virtual ~NurbsBrepConsistencyException ();
	const NurbsBrepConsistencyError&	GetError () const { return error; }
private:
	NurbsBrepConsistencyError	error;
};


}		// namespace Brep

#endif	// NURBSCONSYSTENCYERROR_HPP 
