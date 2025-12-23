#ifndef	POLY_DICT_CONVERSIONS_HPP
#define	POLY_DICT_CONVERSIONS_HPP

#pragma once

#include "GDLExport.h"
#include "GDLDictionary.hpp"
#include "GDLDictFields.hpp"
#include "Poly2DTypes.hpp"
#include "Point2D.hpp"
#include "PolyArcRec.h"
#include "IrregularPolygon2D.hpp"
#include "Polyline2D.hpp"

namespace GDL {

typedef	Geometry::CustomIrregularPolygon2D<Geometry::PolyId, Int32, Geometry::PolyId, Geometry::PolyId>				GDLIrregularPolygon2D;
typedef	Geometry::CustomMultiIrregularPolygon2D<Geometry::PolyId, Int32, Geometry::PolyId, Geometry::PolyId>		GDLIrregularMultiPolygon2D;
typedef	Geometry::CustomMultiPolygon2D<Geometry::PolyId, Int32, Geometry::PolyId, Geometry::PolyId>					GDLRegularizedMultiPolygon2D;

typedef	Geometry::CustomPolyline2D<Geometry::PolyId, Int32, Geometry::PolyId>										GDLPolyline2D;
typedef	Geometry::CustomMultiPolyline2D<Geometry::PolyId, Int32, Geometry::PolyId>									GDLMultiPolyline2D;


enum class DictToPolyConversionErrorType
{
	NoError,
	MissingFieldName,
	InvalidDictionaryType,
	InvalidFieldName,
	InvalidDictionaryPath,
	InvalidPolygon,
	InvalidDictionaryScheme
};

class DictToGDLPoly
{
protected:
	class GDLPolygonData {
	public:
		GS::Array<Point2D>		coordList;
		GS::Array<PolyArcRec>	arcList;
		GS::Array<UIndex>		contourEndList;
		GS::Array<Int32>		edgeInfoList;
		bool					useEdgeInfo;
		bool					isClosedPath;
		Int32					defaultInhEdgeInfo;

		GDLPolygonData ();

	};
	const GDL::Dictionary& polygonDict;

	void AddDictEdgesToPolygonCoords (const GS::Array<GDL::Dictionary> edgesDictArray, GDLPolygonData& polygonData) const;
	DictToPolyConversionErrorType GeneratePolygonData (GDLPolygonData& polygonData) const;

public:

public:
	DictToGDLPoly (const GDL::Dictionary& polygonDict);
};


class GDL_DLL_EXPORT DictToGDLIrregularPolygon2D : public DictToGDLPoly
{
private:
	void SetPolygonEdgeInfo (GDLIrregularPolygon2D&	polygon2D, GDLPolygonData& polygonData) const;

public:
	DictToGDLIrregularPolygon2D (const GDL::Dictionary& polygonDict);
	GDLIrregularPolygon2D ToPolygon (DictToPolyConversionErrorType* errCode = nullptr) const;
};


class GDL_DLL_EXPORT DictToGDLPolyline2D : public DictToGDLPoly
{
private:
	GS::UInt32 GeneratePolylineFlags (bool useEdgeInfo) const;
	void SetPolylineEdgeInfo (GDLPolyline2D& polyline, GDLPolygonData& polygonData) const;

public:
	DictToGDLPolyline2D (const GDL::Dictionary& polygonDict);
	GDLPolyline2D ToPolyLine (DictToPolyConversionErrorType* errCode = nullptr) const;
};


class GDLPolyToDict
{
private:
	void SetDictEdgeInfo (GDL::Dictionary& edgeDict, const Int32& edgeData) const;
	void SetDictEdgeInfo (GDL::Dictionary& edgeDict, const Geometry::PolyId& edgeData) const;

	template<typename PolyType>
	GS::Array<GDL::Dictionary> CreateEdgeDictArray (typename PolyType::ConstEdgeIterator edgeIt, typename PolyType::ConstEdgeIterator* lastEdge, bool useEdgeInfo) const;

	GDL::Dictionary ConstructPolygonDict (bool isClosed,
										  bool useEdgeInfo, Int32 defaultInhEdgeInfo,
										  GDL::Dictionary& contourDict, GS::Array<GDL::Dictionary>* holesArray) const;
public:
	GDLPolyToDict ();

	template<typename PolyType>
	GDL::Dictionary CreatePolygonDict (typename PolyType::ConstContourIterator contourIt, bool useEdgeInfo, Int32 defaultInhEdgeInfo) const;

	template<typename PolyType>
	GDL::Dictionary CreatePolygonDict (typename PolyType::ConstEdgeIterator edgeIt, bool isClosed, typename PolyType::ConstEdgeIterator* lastEdge,
									   bool useEdgeInfo, Int32 defaultInhEdgeInfo) const;

};


enum GDLPolyToDictFlags {
	GDLPolyToDictFlags_Geometry = 0x0000,
	GDLPolyToDictFlags_AddEdgeUserData = 0x0001
};


class GDL_DLL_EXPORT GDLIrregularPolygon2DToDict
{
private:
	const GDLIrregularPolygon2D&	polygon2D;
public:

public:
	GDLIrregularPolygon2DToDict (const GDLIrregularPolygon2D& polygon2D);
	Dictionary		operator () (const GDLPolyToDictFlags& conversionFlags = GDLPolyToDictFlags_Geometry) const;
};


class GDL_DLL_EXPORT GDLPolyLineToDict
{
private:
	const GDLPolyline2D&	polyLine2D;

public:
	GDLPolyLineToDict (const GDLPolyline2D& polyLine2D);
	Dictionary		operator () (const GDLPolyToDictFlags& conversionFlags = GDLPolyToDictFlags_Geometry) const;
};


class GDL_DLL_EXPORT Polygon2DToDict
{
private:
	const Geometry::Polygon2D&	polygon2D;

public:
	Polygon2DToDict (const Geometry::Polygon2D& polygon2D);
	Dictionary		operator () (const GDLPolyToDictFlags& conversionFlags = GDLPolyToDictFlags_Geometry) const;
};


class GDL_DLL_EXPORT Polygon2DToGeometryDict
{
private:
	const Geometry::Polygon2D&	polygon2D;

public:
	Polygon2DToGeometryDict (const Geometry::Polygon2D& polygon2D);
	Dictionary		operator () (const GDLPolyToDictFlags& conversionFlags = GDLPolyToDictFlags_Geometry) const;
};

class GDL_DLL_EXPORT Polyline2DToDict
{
private:
	const Geometry::Polyline2D&	polyLine2D;

public:
	Polyline2DToDict (const Geometry::Polyline2D& polyLine2D);
	Dictionary		operator () (void) const;
};


}
#endif	//POLY_DICT_CONVERSIONS_HPP