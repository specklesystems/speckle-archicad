// *****************************************************************************
// File:			TilerWin.hpp
//
// Description:		Tiler classes for Windows code - obsolete, don't use!
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	TILERWIN_HPP
#define	TILERWIN_HPP

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT

namespace	TilerWin	{

// ---- Base Tiler class ------------------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	Tiler
{

public:
	//Structure of polygon vertex for clipping
	struct ClipVertex2DData {
		float	x, y;
		float	tu, tv;			//arbitrary coordinates in polygon local coord space
		Int32	clipStatus;
	};

private:
	const RECT* srcRect;
	const RECT* dstClipRect;
	double		rotation;

private:
	static	void	ClipEdge (const RECT& clipRect, ClipVertex2DData& insideVertex, ClipVertex2DData& outsideVertex,
							  ClipVertex2DData& clippedVertex, Int32 clippingEdge);

public:
	Tiler () : srcRect (nullptr), dstClipRect (nullptr), rotation (0.0) {}
	virtual ~Tiler () {}

	static	void	GetInvertedOf3x2Matrix (const double (&matrix)[6], double (&invertedMatrix)[6]);

	// 2D polygon clip utility functions
	static	bool	ClipPoly (const RECT& clipRect, GS::Array<ClipVertex2DData>& inVertexList, GS::Array<ClipVertex2DData>& outVertexList);
	static	void	GetBoundRectOfPolyInLocalSpace (const GS::Array<ClipVertex2DData>& vertexList, RECT& boundRect);
	static	void	GetBoundRectOfPoly (const GS::Array<ClipVertex2DData>& vertexList, RECT& boundRect);

	// Rect clipping utility functions
	static  bool	CalculateClippedRects (const RECT& srcBoundRect, const RECT& dstBoundRect,
										   const RECT& srcRect, const RECT* dstClipRect, Int32 dstX, Int32 dstY,
										   RECT* clippedSrcRect, RECT* clippedDstRect);

			void	DoTiling (const RECT* srcRect, Int32 srcOriginX, Int32 srcOriginY,
							  float scaleX, float scaleY, float rotation, Int32 dstX, Int32 dstY,
							  UINT tileSizeX, UINT tileSizeY, const RECT* dstClipRect, Int32 dstOriginX = 0, Int32 dstOriginY = 0);

			void	DoTilingF (const RECT* srcRect, Int32 srcOriginX, Int32 srcOriginY,
							   float scaleX, float scaleY, float rotation, float dstX, float dstY,
							   UINT tileSizeX, UINT tileSizeY, const RECT* dstClipRect, Int32 dstOriginX = 0, Int32 dstOriginY = 0);


	virtual	void	HandleTile (const RECT* srcTileContent, Int32 dstTileContentX, Int32 dstTileContentY,
								const RECT* srcTileRect, const GS::Array<ClipVertex2DData>& tilePoly) = 0;
};


// --- Tiler class measuring the bounding box of the transformed src rect --------------------

class	GRAPHIX_DLL_EXPORT	MeasureTiler: public Tiler
{
private:
	RECT	dstBoundRect;

public:
	// Output members
	RECT	dstDirtyRect;					// Bound rect of clipped transformed src rect
	RECT	srcDirtyRect;					// Needed subrect of src rect

protected:
	void	HandleTile (const RECT* /*srcTileContent*/, Int32 /*dstTileContentX*/, Int32 /*dstTileContentY*/,
						const RECT* /*srcTileRect*/, const GS::Array<ClipVertex2DData>& tilePoly) override;

public:
	MeasureTiler (const RECT& dstBoundRect);
};


}


using namespace TilerWin;

#endif