// *****************************************************************************
// File:			IPointCloud.hpp
//
// Description:		Public pointcloud object interface (threadsafe)
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef		IPOINTCLOUD_HPP
#define		IPOINTCLOUD_HPP

// --- Includes ----------------------------------------------------------------

#include "PointCloudDefinitions.hpp"

#include "PointCloudBox.hpp"
#include "PCPlane.hpp"
#include "IPointCloudRendererDDI.hpp"

// --- Predeclarations ---------------------------------------------------------

class	PointCloudClipData;
class	IPointCloudClip;
class	IPointCloudSource;
class	IStreamingPointCloudSource;


// --- IPointTreeWalkCallback ---------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IPointTreeWalkCallback
{
public:
	struct	Node
	{
		float			x, y, z, r;
		UInt32			pointIndexBeg;
		UInt32			pointIndexEnd;

		Node (float x, float y, float z, float r, UInt32 pointIndexBeg, UInt32 pointIndexEnd):
			x (x),
			y (y),
			z (z),
			r (r),
			pointIndexBeg (pointIndexBeg),
			pointIndexEnd (pointIndexEnd)
			{
			}

		// Ezt a baromsagot, ember...
		Node ():
			x				(0.0f),
			y				(0.0f),
			z				(0.0f),
			r				(0.0f),
			pointIndexBeg	(0),
			pointIndexEnd	(0)
			{
			}
	};

	struct	WalkInfo
	{
		const UInt32*	pointIndices;
		const Node*		parentNode;
		const Node*		node;
		UInt32			depth;
		void*			userData;
		bool			leaf;
	};

public:
	virtual				~IPointTreeWalkCallback ();

	virtual		bool	WalkNode (const WalkInfo& walkInfo) = 0;
	virtual		bool	WalkNodeWithChildOrderInfo (const WalkInfo& walkInfo, const Node** children, UInt32 numOfChildren) = 0;

	// Debug only
	//virtual		void	SetPointColorInformation (const UInt32* colors, UInt32 numOfPoints) = 0;
};


// --- IPointCloud --------------------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IPointCloud
{
public:
	struct	Point
	{
		float	x, y, z;
		UInt32	argbColor;
	};

	enum BuildPolicy	{

		Lazy	=	0,
		Immediate
	};

public:

	virtual	~IPointCloud ();

	// --- Factory functions
	
	static	IPointCloud*		Create (IPointCloudSource& source, BuildPolicy buildpolicy = Lazy, bool keepPointOrder = false);
	static	IPointCloud*		Create (IStreamingPointCloudSource& source, BuildPolicy buildpolicy = Lazy, bool keepPointOrder = false);
	static	IPointCloud*		CreateFromClip (IPointCloudClip* pClip, BuildPolicy buildpolicy = Lazy, bool keepPointOrder = false);
	virtual	IPointCloud*		Clone (BuildPolicy buildpolicy = Lazy, bool keepPointOrder = false) = 0;

	// --- Creating a clip on top of this pointcloud
	
	virtual	IPointCloudClip*	CreateClip (const GS::Array<PC::Plane>& planes, BuildPolicy buildpolicy = Lazy, bool invertResult = false) = 0;
	virtual	IPointCloudClip*	CreateClip (const PointCloudClipData& clipData, BuildPolicy buildpolicy = Lazy) = 0;

	// --- Pointcloud properties
	
	virtual	UInt32				GetNumberOfPoints () const = 0;
	virtual	PC::Box				GetBoundBox () const = 0;

	// --- Reentrant refcounted locking of pointcloud point data
	
	virtual	const Point*		LockVertices () = 0;
	virtual	void				UnlockVertices () = 0;

	// --- Functions for handling asynchronous tree building

	virtual	bool				IsTreeAvailable () const = 0;
	virtual	void				ForceTreeBuild () = 0;

	// --- Tree properties and walk

	virtual	UInt32				GetMaxTreeDepth () const = 0;
	virtual	void				WalkTree (IPointTreeWalkCallback* callback, void* userData) = 0;
	virtual	void				WalkTreeWithChildInfo (IPointTreeWalkCallback* callback, void* userData) = 0;
};


#endif	// IPOINTCLOUD_HPP