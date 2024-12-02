#ifndef VECTORIMAGE_HPP
#define VECTORIMAGE_HPP

#include "VectorImageExport.h"
#include "VectorImageObject.hpp"
#include "ISymbol.hpp"
#include "G2DProcs.h"
#include "Sy2DRenovationStatusTypes.hpp"
#include "SyHatchObject.hpp"

// from GSRoot
#include "GSRoot.hpp"
#include "Cloneable.hpp"
#include "ThreadSafeLazyData.hpp"

// from Geometry
#include "Poly2DTypes.hpp"

// from GSUtils :(
#include "GSUtilsDefs.h"
#include "DrawIndex.hpp"


using OverriddenOpacity = GS::Optional<double>;

namespace Geometry {
	class Transformation2D;
}

namespace GS {
	class XMLOChannel;
	class XMLIChannel;
	class UniString;
}

namespace VBAttr {
	class ExtendedPen;
	class OverriddenPen;
	class OverriddenExtendedPen;
}

class IVectorImagePartialCopy;
class VI2DGeometryInterface;
class ReIDMapCollector;
class PointCloudObject;
class ConstVectorImageIterator;
class VectorImageIterator;
class IGetGradientFillType;
class IPolygonDrawingDirection;

class Sy_EndType;
class Sy_2DHeadType;
class Sy_TextType;
class Sy_PointCloudType;
class Sy_PolyLinType;
class Sy_HotType;
class Sy_LinType;
class Sy_ArcType;
class Sy_SplineType;
class Sy_HatchType;
class Sy_PixMapType;
class Sy_FontType;

struct GS_RGBColor;

namespace VI {
	class Transformer;
	class IAttributeModifier;
	class VectorImageVisitor;
}

namespace VI { namespace HatchGeometryPriority {
	class HatchGeometryPriorityComparer;
}}

namespace GX { namespace Pattern {
	class HatchTran;
}}


struct VI_DLL_CLASS_EXPORT VectorImageDataMask {
	bool geometry : 1;
	bool settings : 1;
	bool material : 1;

	explicit VectorImageDataMask (const bool b) :
		geometry (b),
		settings (b),
		material (b)
	{}

	VectorImageDataMask () :
		VectorImageDataMask (false)
	{}

	bool	IsFullMask () const {
		return geometry && settings && material;
	}
};

class VI_DLL_CLASS_EXPORT VectorImage final {
private:
	friend class ConstVectorImageIterator;
	friend class VectorImageIterator;
	friend class VI::VectorImageVisitor;

	char*	imageData;
	ULong	imageDataLen;
	ULong	allocatedBytes;

	ULong	nElements;
	ULong	nHots;
	ULong	nLine;
	ULong	nPolyLine;
	ULong	nArc;
	ULong	nText;
	ULong	nHatc;
	ULong	nSpline;
	ULong	nFonts;
	ULong	nPicture;
	ULong	nPixMap;
	ULong	nRichText;
	ULong	nPointCloud;

	Int32	defScale;

	struct VectorImageBounds
	{
		Box2DData	boundingBox;
		bool		hangOutOfBox = false;
	};

	GS::ThreadSafeLazyData<VectorImageBounds>	bounds;

	bool			useDrawQueue			:1;
	bool			sortDrawQueue			:1;

	bool			fontsMapped				:1;
	bool			generatedWithOverrides	:1;

	GS::Array<GS::Cloneable<VectorImageObject>>	objects;
	GS::HashTable<GS::Guid, HatchObject>		hatchObjects;

private:
	Sy_EndType*				Element (ULong offset);
	const Sy_EndType*		Element (ULong offset) const;

	void						InvalidateBounds ();
	void						CheckBounds ();
	const VectorImageBounds&	GetVectorImageBounds () const;
	Box2DData					CalcBounds (bool withoutHotspots, bool* hangOutOfBoxParam) const;

	enum AllocationType { Standard = 0, ExactAllocSize = 1, CanDecrease = 2, MakeACopy = 4, SetImageDataLen = 8 };
	GSErrCode				ReallocBytes (ULong bytes, AllocationType allocType);

	GSErrCode				DeleteRecord (Sy_EndType* itemPtr);
	void					AddRecord (const void*		rec,									// can throw
									   const char*		block1 = nullptr,
									   ULong			offset1 = 0,
									   ULong			length1 = 0,
									   const char*		block2 = nullptr,
									   ULong			offset2 = 0,
									   ULong			length2 = 0);
	Sy_EndType*				GetLastEntry ();

	GSErrCode				GetItemPoints_Common (const Box2DData* frame, GS::Array<Coord>& points, SyEnum typeID, bool withoutHotspots) const;

	GSErrCode				Write_TextStyleIndices (GS::OChannel& oc) const;
	GSErrCode				Write_SyObjects (GS::OChannel& oc) const;
	GSErrCode				Write_SyObjectsXML (GS::XMLOChannel& oc) const;
	GSErrCode				Write_Version8_9 (GS::OChannel& oc, const GS::OutputFrame& frame, bool checkSumGeneration = false) const;

	void					Clear_TextStyleIndices ();
	GSErrCode				Read_TextStyleIndices (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode				Read_SyObjects (GS::IChannel& ic);
	GSErrCode				Read_SyObjectsXML (GS::XMLIChannel& ic);
	GSErrCode				ReadVersion1_7 (GS::IChannel& ic, const GS::InputFrame& frame);
	GSErrCode				ReadVersion8_9 (GS::IChannel& ic, const GS::InputFrame& frame);

	void					EmptyVectorImage ();
	void					FillSy_2DHeadType (Sy_2DHeadType* head, bool checkSumGeneration = false) const;
	void					SetConvertedEndOffset (Sy_2DHeadType& head) const;
	void					FillFromSy_2DHeadType (const Sy_2DHeadType& head) ;
	void					SetElements (GS::IChannel& channel, ULong dataLen);					// can throw


	void					TransformSyPolyLine    (const Geometry::Transformation2D&		tran,
													const Sy_PolyLinType*		srcPolyLinePtr,
													Sy_PolyLinType*				myPolyLinePtr,
													Coord**						myPolyCoordsHdl,
													PolyArcRec**				myPolyArcsHdl) const;

	void					TransformSyHatch   (const Geometry::Transformation2D&		tran,
												bool						changeHatchTypeToKeepAppearance,
												const HatchObject&			srcHatchPtr,
												HatchObject&				myHatchPtr,
												IGetGradientFillType*		getFillType) const;

	void					CheckAndClearHatchReferences ();
public:
	VectorImage ();
	VectorImage (const VectorImage& source);						// can throw
	VectorImage (VectorImage&& source);
	~VectorImage ();

	VectorImage&		operator= (const VectorImage& source);		// can throw
	VectorImage&		operator= (VectorImage&& source);

	bool				operator== (const VectorImage& op) const;
	bool				operator!= (const VectorImage& op) const;
	bool				Compare (const VectorImage& op) const;
	bool				Compare (const VectorImage& op, double eps, const VectorImageDataMask& mask) const;

	GSErrCode			WriteForChecksum (GS::OChannel& oc) const;
	GSErrCode			WriteForChecksum (GS::OChannel& oc, double eps, const VectorImageDataMask& mask) const;


	void				Copy (VectorImage& target, IVectorImagePartialCopy& callback) const;

	GSErrCode			CheckAndRepair ();

	GSHandle			GetElements () const;						// can throw
	void				SetSymbolHandle (GSConstHandle imageHdl);	// can throw

	GSErrCode			SetCapacity (ULong capacity);
	GSErrCode			GrowCapacity (ULong capacity);

	Int32				GetScale () const;
	void				SetScale (Int32 defScale);

	[[nodiscard]]
	Box2DData			GetBounds (bool withoutHotspots = false) const;

	bool				IsUsingDrawQueue () const;
	bool				IsUsingSortQueue () const;
	bool				AreThereAnyHotspotsOutOfModel () const;
	bool				WasGeneratedWithOverrides () const;

	void				SetDrawQueueUsing ();
	void				SetSortQueueUsing ();
	void				SetGeneratedWithOverrides (bool generatedWithOverrides);

	bool				IsFontsMapped () const;
	void				SetFontMappingComplete ();

	bool				IsEmpty () const;
	ULong				GetItemCount (bool withoutHotspots = false) const;
	ULong				GetItemCountOfType (SyEnum typeID) const;

	void				Clear ();
	void				DeleteItemsOfType (SyEnum typeID);

	void				Append (const VectorImage&				oper,							// can throw
								IGetGradientFillType*			getFillType,
								const VI::IAttributeModifier&	attrModifier,
								const VI::Transformer&			transformer,
								short							donorLayer		= 0,
								double							dScale			= 100.0);

	GSErrCode			Write (GS::OChannel& channel) const;
	GSErrCode			Read (GS::IChannel& channel);
	GSErrCode			WriteXML (GS::XMLOChannel& channel) const;
	GSErrCode			ReadXML (GS::XMLIChannel& channel);

	void				ExportToHandle (GSHandle handle) const;			// Used in AC API // can throw 
	void				ImportFromHandle (GSConstHandle handle);			// Used in AC API // can throw

	void				OffsetImage (const Geometry::Vector2d& offset);

	GSErrCode			GetItemFramePoints (const Box2DData& frame, GS::Array<Coord>& points, bool withoutHotspots = false) const;
	GSErrCode			GetItemPointsOfType (SyEnum typeID, GS::Array<Coord>& points) const;

	void				AddHotspotRec	(const Sy_HotType&			hotspot);							// can throw

	void				AddLineRec		(const Sy_LinType&			line);								// can throw

	void				AddPolyLineRec	(const Sy_PolyLinType&		polyLine,							// can throw
										const char*					pCoordPtr,
										const char*					pArcsPtr);

	void				AddPolyLine		(const Sy_PolyLinType&		syPolyLine,							// can throw
										const Geometry::Polyline2D&	polyline);

	void				AddWholeGenArc (const VBAttr::ExtendedPen&	pen,								// can throw
										const ADB::AttributeIndex&	pattern,
										short						fragmentIdx,
										DrawIndex					drwIndex,
										const Coord&				origo,
										double						r,
										double						ratio,
										double						mainAxisDir,
										short						determine = 0,
										char						specFor3D = SySymbolic);

	void				AddArcRec (const Sy_ArcType&	arc);								// can throw

	void				AddTextRec (const Sy_TextType&	text,								// can throw
									const char*			conPtr,
									const char*			lstPtr);

	void				AddText	(	short				pen,								// can throw
									short				layer,
									DrawIndex			drwIndex,
									Int32				styleind,
									const Coord&		loc,
									unsigned char		paramInd,
									const char*			text);

	void				AddRichTextRec (const Sy_RichTextType*	richtext);					// can throw

	GSErrCode			AddHatchRec (Sy_HatchType& hatchRef, HatchObject& hatchObj);

	GSErrCode			AddHatchRec (Sy_HatchType&							hatchRef,		// can throw
									 HatchObject&							hatchObj,
									 const Geometry::IrregularPolygon2D&	polygon,
									 const IPolygonDrawingDirection*		drawingDirection);

	GS::Guid			AddHatch (	bool						contVis,					// can throw
									const VBAttr::ExtendedPen&	contPen,
									const VBAttr::ExtendedPen&	fillPen,
									const ADB::AttributeIndex&	fillind,
									Int32						nCoords,
									double*						coords,
									double*						angles,
									UInt32						displayOrder);

	GS::Guid			AddHatchWhole (														// can throw
									bool						contVis,
									const VBAttr::ExtendedPen&	contPen,
									const ADB::AttributeIndex&	contLTyp,
									const VBAttr::ExtendedPen&	fillPen,
									short						bkgPen,
									short						fragmentIdx,
									DrawIndex					drwIndex,
									GX::Pattern::HatchTran		hatchTrafo,
									const ADB::AttributeIndex&	fillind,
									Int32						npb,
									const UInt32*				boends,
									Int32						npc,
									const Coord*				coords,
									const double*				angles,
									const PlaneEq&				plane,
									UInt32						displayOrder,
									const OverriddenOpacity&	overriddenOpacity,
									short						fillTypeDetermination = 0,
									const GS_RGBColor*			bkgColorRGB = nullptr,
									const GS_RGBColor*			fgColorRGB = nullptr,
									char						renovationStatus = VI::SyUndefinedRenovationStatus,
									char						specFor3D = SySymbolic, 
									SyHatchIsForSelection		isSel = SyNormalHatch);

	GS::Guid			AddHatchWhole (														// can throw
									bool							contVis,
									const VBAttr::ExtendedPen&		contPen,
									const ADB::AttributeIndex&		contLTyp,
									const ADB::AttributeIndex&		buildMatIdx,
									const ADB::AttributeIndex&		fillind,
									VBAttr::OverriddenExtendedPen	fillPen,
									VBAttr::OverriddenPen			bkgPen,
									short							fragmentIdx,
									DrawIndex						drwIndex,
									GX::Pattern::HatchTran			hatchTrafo,
									Int32							npb,
									const UInt32*					boends,
									Int32							npc,
									const Coord*					coords,
									const double*					angles,
									const PlaneEq&					plane,
									UInt32							displayOrder,
									short							fillTypeDetermination = 0,
									char							renovationStatus = VI::SyUndefinedRenovationStatus,
									char							specFor3D = SySymbolic);


	void				AddSplineRec (const Sy_SplineType&		spline,							// can throw
									  char*						pCoordPtr,
									  char*						pSDirsPtr);

	void				AddSplineRecConst (const Sy_SplineType&			spline,							// can throw
										   const char*					pCoordPtr,
										   const char*					pSDirsPtr,
										   const Geometry::Vector2d*	offsCo);
	
	void				AddPixMapRec (	const Sy_PixMapType&	pixHeader,					// can throw
										GSConstHandle			pixMemoHdl,
										const char*				mimeType = nullptr);

	void				AddPixMap (	DrawIndex			drwIndex,							// can throw
									GSPixMapHandle		pict,
									Box2DData*			drawnBox,
									bool				mirrored,
									bool				transparent,
									double				rotAngle);

	void				AddFontRec (const Sy_FontType&	font,								// can throw
									const GS::UniString& fontName);

	void				AddSyElement (const Sy_EndType&	elem);								// can throw

	void				AddPointCloudRec (const Sy_PointCloudType&			pointCloudRec,
										  PointCloudObject*					pointCloudObjectPtr);							// can throw

	void					AddPointCloud (PointCloudObject* object, DrawIndex drwIndex, short sy_fragmentIdx);					// can throw
	PointCloudObject*		GetPointCloud (const ConstVectorImageIterator& it);
	const PointCloudObject*	GetPointCloud (const ConstVectorImageIterator& it) const;
	PointCloudObject*		GetPointCloud (const Sy_PointCloudType& pc);

	const HatchObject&		GetHatchObject (const Sy_HatchType& hatchRef) const;
	HatchObject&			GetHatchObject (const Sy_HatchType& hatchRef);
	bool					AddHatchObject (const HatchObject& hatch);
	const Sy_HatchType*		GetSyHatchType (const GS::Guid& hatchUniqueId) const;
	
	const GS::HashTable<GS::Guid, HatchObject>&	GetConstHatchObjects (void) const;
	const HatchObject*							GetHatchObject (const GS::Guid& hatchId) const;

	bool					GetContinousPolylines (GS::Array<Geometry::Polyline2D>& resultPolylines) const;

	void				GetUsedAttributes (GS::Array<ADB::AttributeIndex>& lineTypes, GS::Array<ADB::AttributeIndex>& fills, GS::Array<ADB::AttributeIndex>& buildingMaterials, GS::Array<ADB::AttributeIndex>& surfaces) const;

	void				ReindexUsedAttributes (const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& lineTypeMapping,
											   const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& fillMapping,
											   const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& buildingMaterialMapping,
											   const GS::HashTable<ADB::AttributeIndex, ADB::AttributeIndex>& surfaceMapping);

	void				Strip (const Geometry::IrregularPolygon2D& cutPoly, VectorImage* resultingImage, const Geometry::Boundary cutWithBoundary = Geometry::Boundary_Opened, bool stripHotspots = false) const;				// can throw
	void				Sort (GS::CmpFunction* sortFunc, VectorImage* resultingImage) const;								// can throw

	void				Transform (const VI::Transformer& transformer);															// can throw
	void				Transform (const VI::Transformer& transformer, VectorImage* resultingImage) const;						// can throw

	USize				GetSizeInBytes (void) const;

	void				ExportTo (VI2DGeometryInterface& dest) const;
	void				ImportFrom (VI2DGeometryInterface& src, const VI::HatchGeometryPriority::HatchGeometryPriorityComparer& comparer);

	static void			MarkPolyEdgesVerts (Geometry::IrregularPolygon2D& poly);
	static void			MarkPolyEdgesVerts (Geometry::IrregularPolygon2D& poly, const GS::Guid& polyGUID, ReIDMapCollector& reID);
private:
	static void			MarkPolyEdgesVerts (Geometry::IrregularPolygon2D& poly, const GS::Guid& polyGUID, ReIDMapCollector* reID);

	void				MoveFromVectorImage (VectorImage&& source);
};

/*	Implement this interface to specify which elements in the VectorImage
	should be copied to the new VectorImage.
	- CopyCurrent(): return true if should copy; false if shouldn't
*/
class VI_DLL_CLASS_EXPORT IVectorImagePartialCopy {
public:
	virtual bool CopyCurrent (const ConstVectorImageIterator& currentElem) = 0;
	virtual ~IVectorImagePartialCopy ();
};



#include "VectorImageInline.hpp"

#endif
