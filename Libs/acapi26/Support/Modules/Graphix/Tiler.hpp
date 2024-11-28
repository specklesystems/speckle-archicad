// *****************************************************************************
// File:			Tiler.hpp
//
// Description:		Tiler classes
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef	TILER_HPP
#define	TILER_HPP

#include "GraphixDefinitions.hpp"		// GRAPHIX_DLL_EXPORT

// ---- Base Tiler class ------------------------------------------------------------------------

class	GRAPHIX_DLL_EXPORT	Tiler
{
public:
	//Rect structure
	struct	Rect
	{
		Int32	left, top, right, bottom;

		Rect ():
			left	(0),
			top		(0),
			right	(0),
			bottom	(0)
		{
		}

		Rect (Int32	left, Int32	top, Int32 right, Int32 bottom):
			left	(left),
			top		(top),
			right	(right),
			bottom	(bottom)
		{
		}

		bool	IsEmpty ()
		{
			return IsRectEmpty (this);
		}
	};

public:
	//Structure of polygon vertex for clipping
	struct ClipVertex2DData {
		float	x, y;
		float	tu, tv;			//arbitrary coordinates in polygon local coord space
		Int32	clipStatus;
	};


protected:
	static	bool	IntersectRect (Rect* lprcDst, const Rect* lprcSrc1, const Rect* lprcSrc2);
	static	bool	IsRectEmpty (const Rect* lprc);
	static	void	OffsetRect (Rect* lprc, Int32 dx, Int32 dy);
	static	void	InflateRect (Rect* lprc, Int32 dx, Int32 dy);
	static	bool	UnionRect (Rect* lprcDst, const Rect* lprcSrc1, const Rect* lprcSrc2);
	static	void	SetRectEmpty (Rect* lprc);

private:
	static	void	ClipEdge (const Rect& clipRect, ClipVertex2DData& insideVertex, ClipVertex2DData& outsideVertex,
							  ClipVertex2DData& clippedVertex, Int32 clippingEdge);

public:
	Tiler () {}
	virtual ~Tiler ();

	static	void	GetInvertedOf3x2Matrix (const double (&matrix)[6], double (&invertedMatrix)[6]);

	// 2D polygon clip utility functions
	static	bool	ClipPoly (const Rect& clipRect, GS::ArrayFB<ClipVertex2DData, 8>& inVertexList, GS::ArrayFB<ClipVertex2DData, 8>& outVertexList);
	static	void	GetBoundRectOfPolyInLocalSpace (const GS::Array<ClipVertex2DData>& vertexList, Rect& boundRect);
	static	void	GetBoundRectOfPoly (const GS::Array<ClipVertex2DData>& vertexList, Rect& boundRect);

	// Rect clipping utility functions
	static  bool	CalculateClippedRects (const Rect& srcBoundRect, const Rect& dstBoundRect,
										   const Rect& srcRect, const Rect* dstClipRect, Int32 dstX, Int32 dstY,
										   Rect* clippedSrcRect, Rect* clippedDstRect);

			void	DoTiling (const Rect* srcRect, Int32 srcOriginX, Int32 srcOriginY,
							  float scaleX, float scaleY, float rotation, Int32 dstX, Int32 dstY,
							  UInt32 tileSizeX, UInt32 tileSizeY, const Rect* dstClipRect, Int32 dstOriginX = 0, Int32 dstOriginY = 0);

			void	DoTilingF (const Rect* srcRect, Int32 srcOriginX, Int32 srcOriginY,
							   float scaleX, float scaleY, float rotation, float dstX, float dstY,
							   UInt32 tileSizeX, UInt32 tileSizeY, const Rect* dstClipRect, Int32 dstOriginX = 0, Int32 dstOriginY = 0);


	virtual	void	HandleTile (const Rect* srcTileContent, Int32 dstTileContentX, Int32 dstTileContentY,
								const Rect* srcTileRect, const GS::Array<ClipVertex2DData>& tilePoly) = 0;
};


// --- Tiler class measuring the bounding box of the transformed src rect --------------------

class	GRAPHIX_DLL_EXPORT	MeasureTiler: public Tiler
{
private:
	Rect	dstBoundRect;

public:
	// Output members
	Rect	dstDirtyRect;					// Bound rect of clipped transformed src rect
	Rect	srcDirtyRect;					// Needed subrect of src rect

protected:
	void	HandleTile (const Rect* /*srcTileContent*/, Int32 /*dstTileContentX*/, Int32 /*dstTileContentY*/,
						const Rect* /*srcTileRect*/, const GS::Array<ClipVertex2DData>& tilePoly) override;

public:
	MeasureTiler (const Rect& dstBoundRect);
};

#endif