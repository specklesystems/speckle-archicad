// *********************************************************************************************************************
// Description:		Class interface and implementations for body member comparison
//
// Module:			GSModeler
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (BODYMEMBERCOMPARATOR_HPP)
#define BODYMEMBERCOMPARATOR_HPP 


#pragma once

// --- Includes --------------------------------------------------------------------------------------------------------

// from GSModeler
#include	"Model3D/Model3DExport.h"  

// from GSRoot
#include	"Definitions.hpp"

// from Geometry
#include	"Vector3D.hpp"


class	Wrapping;

namespace Modeler {


class	MODEL3D_DLL_EXPORT	IBodyMemberComparator
{
public:
	virtual			~IBodyMemberComparator ();

	// Compare functions call the inherited class' functions and return if the comparison shall be continued
	bool			Compare (const Vector3D& v1, const Vector3D& v2)				{ return CmpVector3Ds (v1, v2);				}	// Coord3D is the same typedef as Vector3D so an overload would not compile at the moment
	bool			Compare (const Int32 i1, const Int32 i2)						{ return CmpIntegers (i1, i2);				}
	bool			Compare (const UInt32 u1, const UInt32 u2)						{ return CmpUIntegers (u1, u2);				}
	bool			Compare (const double d1, const double d2)						{ return CmpDoubles (d1, d2);				}
	bool			Compare (const Wrapping& w1, const Wrapping& w2)				{ return CmpWraps (w1, w2);					}
	bool			CompareItemCounts (const Int32& count1, const Int32& count2)	{ return CompareItemCnt (count1, count2);	}

protected:
	virtual	bool	CmpVector3Ds (const Vector3D& v1, const Vector3D& v2) = 0;
	virtual	bool	CmpIntegers (const Int32 i1, const Int32 i2) = 0;
	virtual	bool	CmpUIntegers (const UInt32 u1, const UInt32 u2) = 0;
	virtual	bool	CmpDoubles (const double d1, const double d2) = 0;
	virtual	bool	CmpWraps (const Wrapping& w1, const Wrapping& w2) = 0;
	virtual	bool	CompareItemCnt (const Int32& count1, const Int32& count2) = 0;
};

// ------------------------------------------------------------------
// continues while previous comparisons result "equal"
// ------------------------------------------------------------------
class	MODEL3D_DLL_EXPORT	BodyMemberEqualityChecker : public IBodyMemberComparator
{
public:
	enum class	CompareResult : short {
		Equal,
		NotEqual
	};

					BodyMemberEqualityChecker (const double eps);
	virtual			~BodyMemberEqualityChecker ();

	CompareResult	GetCompareResult () const	{ return m_compareResult;	}

protected:
	virtual	bool	CmpVector3Ds (const Vector3D& v1, const Vector3D& v2) override;
	virtual	bool	CmpIntegers (const Int32 i1, const Int32 i2) override;
	virtual	bool	CmpUIntegers (const UInt32 u1, const UInt32 u2) override;
	virtual	bool	CmpDoubles (const double d1, const double d2) override;
	virtual	bool	CmpWraps (const Wrapping& w1, const Wrapping& w2) override;
	virtual	bool	CompareItemCnt (const Int32& count1, const Int32& count2) override;

private:
	const double	m_eps;
	CompareResult	m_compareResult;
};


// ------------------------------------------------------------------
// continues while previous comparisons result "less or equal"
// ------------------------------------------------------------------
class	MODEL3D_DLL_EXPORT	BodyMemberSorter : public IBodyMemberComparator
{
public:
	enum class	CompareResult : short {
		Less,
		Equal,
		Greater
	};

					BodyMemberSorter ();
	virtual			~BodyMemberSorter ();

	CompareResult	GetCompareResult () const	{ return m_compareResult;	}

protected:
	virtual	bool	CmpVector3Ds (const Vector3D& v1, const Vector3D& v2) override;
	virtual	bool	CmpIntegers (const Int32 i1, const Int32 i2) override;
	virtual	bool	CmpUIntegers (const UInt32 u1, const UInt32 u2) override;
	virtual	bool	CmpDoubles (const double d1, const double d2) override;
	virtual	bool	CmpWraps (const Wrapping& w1, const Wrapping& w2) override;
	virtual	bool	CompareItemCnt (const Int32& count1, const Int32& count2) override;

private:
	CompareResult	m_compareResult;
};


}	// namespace Modeler

#endif // BODYMEMBERCOMPARATOR_HPP
