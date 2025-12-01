// *********************************************************************************************************************
// Description:		This class represents a knot vector of a NURBS curve or surface.
//
// Module:			Geometry
// Namespace:		Geometry
//
// SG compatible
// *********************************************************************************************************************

#ifndef KNOTVECTOR_HPP
#define KNOTVECTOR_HPP

// from GSRoot
#include "Array.hpp"

// from Geometry
#include "GeometricDefinitions.h"
#include "RealNumber.h"

namespace Geometry {

class GEOMETRY_DLL_EXPORT KnotVector {



private:
	GS::Array<double>	knotValues;
	UInt32				degree;

public:
	KnotVector () : knotValues (), degree (0)
	{
		// do nothing
	}

	// Degree can be invalid (0) and set later.
	explicit KnotVector (const GS::Array<double>& values, UInt32 degree = 0)
		: knotValues (values)
		, degree (degree)
	{
		// do nothing
	}

	// Degree can be invalid (0) and set later.
	explicit KnotVector (const GS::Array<double>&& values, UInt32 degree = 0)
		: knotValues (values)
		, degree (degree)
	{
		// do nothing
	}

	// Array-wrapper methods
	USize	GetSize			() const					{ return knotValues.GetSize ();			}
	void	SetSize			(USize size)				{ knotValues.SetSize (size);			}
	double	GetFirst		() const					{ return knotValues.GetFirst ();		}
	double	GetLast			() const					{ return knotValues.GetLast ();			}
	void	Insert			(UIndex i, double value)	{ knotValues.Insert (i, value);			}
	double	operator[]		(UIndex i) const			{ return knotValues[i];					}
	double&	operator[]		(UIndex i)					{ return knotValues[i];					}

	GSErrCode	ReadVersion1	(GS::IChannel& ic);
	GSErrCode	WriteVersion1	(GS::OChannel& oc) const;
	GSErrCode	ReadVersion2	(GS::IChannel& ic);
	GSErrCode	WriteVersion2	(GS::OChannel& oc) const;

	// knot vector functionality
	const GS::Array<double>& GetValues		() const			{ return knotValues;										}
	bool	IsEmpty							() const			{ return knotValues.IsEmpty () && DBVERIFY (degree == 0);	}
	void	Clear							()					{ knotValues.Clear (); degree = 0;							}
	UInt32	GetDegree						() const			{ return degree;											}
	void	SetDegree						(UInt32 d)			{ degree = d;												}
	bool	IsValid							() const;
	bool	IsPeriodic						() const;
	bool	IsFloatBegin					() const;
	bool	IsFloatEnd						() const;
	bool	IsQuasiUniform					() const;
	UInt32	GetMultiplicity					(double knot) const	{ return knotValues.Count (knot);	}
	void	GetKnotValuesAndMultiplicities	(GS::Array<double>* kValues, GS::Array<Int32>* multis) const;
	bool	IsEqual							(const KnotVector& other, double eps) const;
	double	GetDomainMin					() const;
	double	GetDomainMax					() const;
	UIndex	GetDomainMinSpanIndex			() const;
	UIndex	GetDomainMaxSpanIndex			() const;
	UIndex	FindKnotSpanInDomain			(double t) const;
	UIndex	FindMinKnotSpan					(double t) const;
	UIndex	FindMaxKnotSpan					(double t) const;

	ULong	GetUsedBytes					() const;
	ULong	GetHeapUsedBytes				() const;

	GSErrCode Store (GS::ObjectState& os) const;
	GSErrCode Restore (const GS::ObjectState& os);
	GSErrCode Write (GS::OChannel& oc) const;
	GSErrCode Read (GS::IChannel& ic);
};
	
}	// namespace Geometry

#endif	// KNOTVECTOR_HPP