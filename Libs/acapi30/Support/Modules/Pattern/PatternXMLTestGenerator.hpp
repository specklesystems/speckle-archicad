// Contact person : KiP

#ifndef PATTERN_XMLTEST_GENERATOR_HPP
#define PATTERN_XMLTEST_GENERATOR_HPP

#pragma once

// from GSRoot
#include "Owner.hpp"
#include "HashSet.hpp"

// from GSXMLUtils
#include "GSXMLDOMBuilder.hpp"

// from Pattern
#include "LinePattern.h"


namespace GX {
namespace Pattern {

class PATTERN_DLL_EXPORT LinePatternXMLDump : public LinePatternPrimitivesDrawer
{
public:
	LinePatternXMLDump (GS::XMLOChannel& oc);
	virtual ~LinePatternXMLDump ();

	virtual	GSErrCode DrawLine (const Geometry::PolyId* edgeId, const Sector* sector) override;

private:
	GS::XMLOChannel& oc;
};


struct PATTERN_DLL_EXPORT XMLTestInputBase
{
	LineInfo				lineInfo;
	double					tolerance;
	GS::Owner<Box2DData>	box;

	XMLTestInputBase ();
	XMLTestInputBase (const LineInfo& lineInfo, double tolerance, const Box2DData* drawBox);
	virtual ~XMLTestInputBase ();

	virtual void WriteXML (GS::XMLOChannel& oc) const;
	virtual void ReadXML (GS::XMLIChannel& ic);
};

struct PATTERN_DLL_EXPORT DrawLineXMLTestInput : public XMLTestInputBase
{
	Coord begC;
	Coord endC;

	DrawLineXMLTestInput ();
	DrawLineXMLTestInput (const Coord& begC,const Coord& endC, const LineInfo& lineInfo, double tolerance, const Box2DData* drawBox);
	virtual ~DrawLineXMLTestInput ();

	virtual void WriteXML (GS::XMLOChannel& oc) const override;
	virtual void ReadXML (GS::XMLIChannel& ic) override;
};

struct PATTERN_DLL_EXPORT DrawPolyLineXMLTestInput : public XMLTestInputBase
{
	Geometry::Polyline2D polyLine;
	GX::Pattern::PolyLinePerSegmentDrawMode drawSegmentMode;

	DrawPolyLineXMLTestInput ();
	DrawPolyLineXMLTestInput (const Geometry::Polyline2D& polyLine, const LineInfo& lineInfo, GX::Pattern::PolyLinePerSegmentDrawMode drawSegmentMode, double tolerance, const Box2DData* drawBox);
	virtual ~DrawPolyLineXMLTestInput ();

	virtual void WriteXML (GS::XMLOChannel& oc) const override;
	virtual void ReadXML (GS::XMLIChannel& ic) override;
};

struct PATTERN_DLL_EXPORT DrawPolygonContourXMLTestInput : public XMLTestInputBase
{
	Geometry::IrregularPolygon2D polygon;
	GS::HashTable<UIndex, bool> drawingDirections;

	DrawPolygonContourXMLTestInput ();
	DrawPolygonContourXMLTestInput (const Geometry::IrregularPolygon2D& polygon, const IPolygonDrawingDirection* drawDirection, const LineInfo& lineInfo, double tolerance, const Box2DData* drawBox);
	virtual ~DrawPolygonContourXMLTestInput ();

	virtual void WriteXML (GS::XMLOChannel& oc) const override;
	virtual void ReadXML (GS::XMLIChannel& ic) override;
};

struct PATTERN_DLL_EXPORT DrawArcXMLTestInput : public XMLTestInputBase
{
	Coord	origo;
	Coord	begC;
	double	arcAngle;

	DrawArcXMLTestInput ();
	DrawArcXMLTestInput (const Coord& origo, const Coord& begC, double arcAngle, const LineInfo& lineInfo, double tolerance, const Box2DData* drawBox);
	virtual ~DrawArcXMLTestInput ();

	virtual void WriteXML (GS::XMLOChannel& oc) const override;
	virtual void ReadXML (GS::XMLIChannel& ic) override;
};


class XMLTestGeneratorBase
{
public:
	XMLTestGeneratorBase (const GS::UniString& outputFolderName, const GS::UniString& testFileNameBegin);
	virtual ~XMLTestGeneratorBase ();

	void GenerateTestCase (const XMLTestInputBase* input);

private:
	virtual GS::UniString GetTestFunctionName () const = 0;
	virtual void WriteTestInputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) = 0;
	virtual void WriteTestOutputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) = 0;

	GS::UniString GenerateTestFileName (const LineInfo& lineInfo) const;
	void ExportDomBuilder (const GS::UniString& fileName, GSXML::DOMBuilder& domBuilder);
	void SetOutputFolderLocation ();

	const GS::UniString			outputFolderName;
	IO::Location				outputFolderLocation;
	const GS::UniString			testFileNameBegin;
	GS::HashSet<GS::UniString>	testFileNames;
};

class DrawLineXMLTestGenerator : public XMLTestGeneratorBase
{
public:
	DrawLineXMLTestGenerator ();
	virtual ~DrawLineXMLTestGenerator ();
	
private:
	virtual GS::UniString GetTestFunctionName () const override;
	virtual void WriteTestInputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) override;
	virtual void WriteTestOutputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) override;
};

class DrawPolyLineXMLTestGenerator : public XMLTestGeneratorBase
{
public:
	DrawPolyLineXMLTestGenerator ();
	virtual ~DrawPolyLineXMLTestGenerator ();

private:
	virtual GS::UniString GetTestFunctionName () const override;
	virtual void WriteTestInputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) override;
	virtual void WriteTestOutputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) override;
};

class DrawArcXMLTestGenerator : public XMLTestGeneratorBase
{
public:
	DrawArcXMLTestGenerator ();
	virtual ~DrawArcXMLTestGenerator ();

private:
	virtual GS::UniString GetTestFunctionName () const override;
	virtual void WriteTestInputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) override;
	virtual void WriteTestOutputToXML (GS::XMLOChannel& oc, const XMLTestInputBase* input) override;
};


}
}

#endif

