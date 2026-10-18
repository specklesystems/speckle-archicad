// *****************************************************************************
// File:			IPointCloudClip.hpp
//
// Description:		Public pointcloud clip object interface (threadsafe)
//
// Project:			GRAPHISOFT PointCloud
//
// Contact person:	DG
//
// SG compatible
// *****************************************************************************

#ifndef		IPOINTCLOUDCLIP_HPP
#define		IPOINTCLOUDCLIP_HPP

// --- Includes ----------------------------------------------------------------

#include "Ref.hpp"

#include "PointCloudDefinitions.hpp"

#include "IPointCloud.hpp"
#include "PCPlane.hpp"
#include "PointCloudBox.hpp"

// --- Predeclarations ---------------------------------------------------------

class	IPointTreeWalkCallback;

// --- PointCloudClipData (non-threadsafe) -------------------------------------

class	POINTCLOUD_DLL_EXPORT	PointCloudClipData
{
public:
	typedef GS::Ref<UInt8, GS::AtomicCounter>	BitFieldRef;

	BitFieldRef	bitField;					// nullptr ref means empty or full clip
	UInt32		numberOfPoints;				// Number of all points in the bitfield
	bool		emptyClip;

public:
	PointCloudClipData ();
	PointCloudClipData (const PointCloudClipData& src);

	PointCloudClipData& operator= (const PointCloudClipData& src);

	PointCloudClipData (const UInt8* bitField, UInt32 numberOfPoints, bool emptyClip);						// Creates a copy of bitfield
	PointCloudClipData (BitFieldRef bitField, UInt32 numberOfPoints, bool emptyClip);	// Stores this ref of bitfield

	PointCloudClipData Clone () const;

	UInt32			GetNumberOfUnclippedPoints () const;
	UInt32			GetNumberOfBytes () const;

	bool			IsEmptyClip () const;
	bool			IsFullClip () const;

	void			SetBit		(UIndex bitIndex);
	void			ClearBit	(UIndex bitIndex);

	static PointCloudClipData CreateEmpty () {
		return PointCloudClipData (nullptr, 0, /*emptyClip*/ true);
	}

	static PointCloudClipData CreateFull () {
		return PointCloudClipData (nullptr, 0, /*emptyClip*/ false);
	}

};


// --- IPointCloudClip ----------------------------------------------------------

class	POINTCLOUD_DLL_EXPORT	IPointCloudClip
{
public:
	enum BuildPolicy	{

		Lazy	=	0,
		Immediate
	};

public:
	virtual	~IPointCloudClip ();

	// --- Clip data

	virtual	IPointCloud*				GetParentObject () const = 0;
	virtual	PointCloudClipData			GetClipData () const = 0;
	virtual	UInt32						GetNumberOfUnclippedPoints () const = 0;

	// --- Creating new clips from this clip

	virtual	IPointCloudClip*	Clone				(BuildPolicy buildpolicy = Lazy) = 0;
	virtual	IPointCloudClip*	CreateClip 			(const GS::Array<PC::Plane>& planes, BuildPolicy buildpolicy = Lazy, bool invertResult = false) = 0;
	virtual IPointCloudClip*	CreateClip			(const PointCloudClipData& newClipData, BuildPolicy buildPolicy = Lazy, bool invertResult = false) = 0;
	virtual IPointCloudClip*	MaskClip			(const PointCloudClipData& maskClipData, BuildPolicy buildPolicy = Lazy, bool invertResult = false) = 0;


	// --- PointcloudClip properties

	virtual	PC::Box						GetBoundBox () const = 0;

	// --- Functions for handling asynchronous tree building

	virtual	bool						IsTreeAvailable () const = 0;
	virtual	void						ForceTreeBuild () = 0;

	// --- Tree properties and walk

	virtual const IPointCloud::Point*	LockVertices () const = 0;
	virtual void						UnlockVertices () const = 0;

	virtual	UInt32						GetMaxTreeDepth () const = 0;
	
	virtual	void						WalkTree (IPointTreeWalkCallback* callback, void* userData) = 0;
	virtual	void						WalkTreeWithChildInfo (IPointTreeWalkCallback* callback, void* userData) = 0;
};

#endif	// IPOINTCLOUDCLIP_HPP