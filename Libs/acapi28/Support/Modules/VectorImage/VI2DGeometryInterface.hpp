#ifndef IPARPROFILEGEOMETRY_HPP
#define IPARPROFILEGEOMETRY_HPP

#pragma once

// from GSRoot
#include "CountedPtr.hpp"
#include "GSFriend.hpp"

// from VectorImage
#include "IGeomElemIDResolver.hpp"
#include "VectorImageExport.h"

namespace GS {
	class Guid;
}

class Sy_HatchType;
class HatchObject;
class VIMultiPoly2D; 
class GeomElemIDDescendencyMap; 
class VectorImage;

namespace VI {
namespace HatchGeometryPriority {
	class HatchGeometryPriorityComparer;
}
}

class VI_DLL_CLASS_EXPORT VI2DGeometryInterface
{
public:
	class Iterator;
	class ConstIterator;

	virtual ~VI2DGeometryInterface ();
	virtual void							AddNewPoly (GS::Friend<VectorImage>, const GS::Guid& polyGUID, VIMultiPoly2D* newPoly, const Sy_HatchType* hatchType) = 0; //ownership of newPoly is passed here! 
	virtual Iterator						Begin () = 0;
	virtual Iterator						End () = 0;
	virtual ConstIterator					BeginConst () const = 0;
	virtual ConstIterator					EndConst () const = 0;
	virtual IGeomElemIDResolverPtr			GetGeomElemIDResolver () = 0;

	virtual void							GetOriginalHatchObject (const GS::Guid& polyGuid, HatchObject& emptyHatchObj) const = 0;
	virtual const GeomElemIDDescendencyMap&	GetEdgeDescendants () const = 0;
	virtual const GeomElemIDDescendencyMap&	GetVertexDescendants () const = 0;
	virtual void							MakeAllMarkersUnique () = 0;	//Each edge or vertex gets a marker that is unique, therefore may be used as ID!
	virtual void							GetNewVectorImage (VectorImage& newVI, const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer) = 0;

	virtual GS::Array<VI2DGeometryInterface::Iterator>		GetPriorityOrderedPolys			(const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer) = 0;
	virtual GS::Array<VI2DGeometryInterface::ConstIterator>	GetConstPriorityOrderedPolys	(const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer) const = 0;
};

class VI_DLL_CLASS_EXPORT VIMGuidPolyPair
{
public:
	VIMGuidPolyPair (const GS::Guid& inVIMPolyGuid, VIMultiPoly2D& inVIMPoly);

	const GS::Guid&			GetVIMPolyGUID () const;
	VIMultiPoly2D&			GetVIMPoly () const;

private:
	const GS::Guid&	vimPolyGuid;
	VIMultiPoly2D&  vimPoly;
};

class VI_DLL_CLASS_EXPORT ConstVIMGuidPolyPair
{
public:
	explicit ConstVIMGuidPolyPair (const VIMGuidPolyPair vimGuidPolyPair);
	ConstVIMGuidPolyPair (const GS::Guid& inVIMPolyGuid, const VIMultiPoly2D& inVIMPoly);

	const GS::Guid&			GetVIMPolyGUID () const;
	const VIMultiPoly2D&	GetVIMPoly () const;

private:
	const GS::Guid&	vimPolyGuid;
	const VIMultiPoly2D&  vimPoly;
};


class VI_DLL_CLASS_EXPORT VI2DGeometryInterface::Iterator
{
public:
	class ImplInterface;

	Iterator (const Iterator& src);
	Iterator (GS::CountedPtr<ImplInterface>& implInit);
	virtual ~Iterator ();

	VIMGuidPolyPair operator* () const;

	void	 		operator++ ();
	bool			operator== (const Iterator& rhs) const;
	bool 			operator!= (const Iterator& rhs) const;

private:
	GS::CountedPtr<ImplInterface>			impl;
};


class VI_DLL_CLASS_EXPORT VI2DGeometryInterface::ConstIterator
{
public:
	class ConstImplInterface;

	ConstIterator (const ConstIterator& src);
	ConstIterator (GS::CountedPtr<ConstImplInterface>& implInit);
	virtual ~ConstIterator ();

	ConstVIMGuidPolyPair	operator* () const;

	void	 				operator++ ();
	bool					operator== (const ConstIterator& rhs) const;
	bool 					operator!= (const ConstIterator& rhs) const;

private:
	GS::CountedPtr<ConstImplInterface>	impl;
};


class VI_DLL_CLASS_EXPORT VI2DGeometryInterface::Iterator::ImplInterface
{
public: 
	virtual ~ImplInterface ();

	virtual VIMGuidPolyPair GetVIMGuidPolyPair () const = 0;

	virtual void 			operator++ () = 0;
	virtual bool 			operator== (const ImplInterface& rhs) const = 0;
	virtual ImplInterface*	Clone () const = 0;
};


class VI_DLL_CLASS_EXPORT VI2DGeometryInterface::ConstIterator::ConstImplInterface
{
public:
	virtual ~ConstImplInterface ();

	virtual ConstVIMGuidPolyPair	GetConstVIMGuidPolyPair () const = 0;

	virtual void 					operator++ () = 0;
	virtual bool 					operator== (const ConstImplInterface& rhs) const = 0;
	virtual ConstImplInterface*		Clone () const = 0;
};


#endif //IPARPROFILEGEOMETRY_HPP
