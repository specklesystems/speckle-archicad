// *********************************************************************************************************************
// Description:		PointCloudManager
//					Singleton object that provides global access to point cloud view objects, including read, write
//					and caching.
//
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (POINTCLOUDMANAGER_HPP)
#define POINTCLOUDMANAGER_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "HashTable.hpp"
#include "HashSet.hpp"
#include "Lock.hpp"

// from PointCloudLib
#include "PCMatrix.hpp"
#include "PCPlane.hpp"
#include "IPointCloudClip.hpp"
#include "PointCloudManagerDefinitions.hpp"

// from PointCloudManager
#include "PointCloudViewFwd.hpp"
#include "PointCloudFilterFwd.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace GS {
	class IChannel;
	class OChannel;
	class LazyInstantiationPolicy;
}

namespace PointCloud {

class PointCloudCachable;
class PointCloudClipCachable;
class PointCloudClipDataCachable;
class MatrixCachable;

// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

class POINTCLOUDMANAGER_DLL_EXPORT PointCloudManager
{
public:
	// -----------------------------------------------------------------------------------------------------------------
	// Describes how to combine results of cuts with single planes.
	// -----------------------------------------------------------------------------------------------------------------
	enum PlaneCutMode
	{
		PlaneCutAnd,	// intersection of single results
		PlaneCutOr		// union of single results
	};

// enable access to private constructor
friend class GS::LazyInstantiationPolicy;

private:
	// disabled
	PointCloudManager (const PointCloudManager& /* src */);
	PointCloudManager& operator= (const PointCloudManager& /* src */);

	// for GS::LazyInstantiationPolicy
	PointCloudManager ();

public:
	static PointCloudManager& GetInstance ();
	~PointCloudManager ();

	ConstViewPtr	CreatePointCloudView	(const PC::PointSourceId& pointSourceId);
	
	ConstViewPtr	Empty					(const ConstViewPtr& view);
	ConstViewPtr	Transform				(const ConstViewPtr& view, const PC::Matrix& transformation);
	ConstViewPtr	Filter					(const ConstViewPtr& view, ConstFilterPtr filter);
		
	GSErrCode Read			(ConstViewPtr& view, GS::IChannel& ic);
	GSErrCode Write			(const ConstViewPtr& view, GS::OChannel& oc);

	GSErrCode QuickRead		(ConstViewPtr& view, GS::IChannel& ic);
	GSErrCode QuickWrite	(const ConstViewPtr& view, GS::OChannel& oc);

private:
	ConstViewPtr	CreatePointCloudViewInternal	(const PC::PointSourceId& pointSourceId,
														const PC::ContentId& contentId,
														const PC::Box& boundingBox,
														const PC::Matrix& transformation,
														const PointCloudClipData& clipData);

	ConstViewPtr	ClipInternal					(const ConstViewPtr& view, IPointCloudClip* clip);
	
	// Only for PointCoudView.
	// Internally, use @...Internal variants instead.
	friend class PointCloudView;
	ConstPointCloudClipDataPtr	GetClipData		(const PC::ClipDataId& clipDataId);
	void						GetCloudAndClip	(const PC::PointSourceId& pointSourceId,
												const PC::ClipDataId& clipDataId,
												ConstPointCloudPtr& cloud,
												ConstPointCloudClipPtr& clip);
	
	// only for PointCloudCachable
	friend class PointCloudCachable;
	void	Drop (const PointCloudCachable* cachedCloud);

	// only for PointCoudClipCachable
	friend class PointCloudClipCachable;
	void	Drop (const PointCloudClipCachable* cachedClip);

	// only for PointCoudClipCachable
	friend class PointCloudClipDataCachable;
	void	Drop (const PointCloudClipDataCachable* cachedClipData);

	// internal methods that are unsafe and must be called from a synchronized context
	void	DropCloudAndRelatedClips (const PC::PointSourceId& pointSourceId);

	void	GetClipDataInternal		(const PC::ClipDataId& clipDataId, ConstPointCloudClipDataPtr& clipData);
	void	GetCloudAndClipInternal	(const PC::PointSourceId& pointSourceId,
									const PC::ClipDataId& clipDataId,
									ConstPointCloudPtr& cloud,
									ConstPointCloudClipPtr& clip);
	void	GetCloudInternal		(const PC::PointSourceId& pointSourceId, ConstPointCloudPtr& cloud);
	
	ConstPointCloudClipDataPtr	ShareClipData	(const PointCloudClipData& clipData);
	ConstPointCloudClipPtr		ShareClip		(const PC::PointSourceId& pointSourceId,
												const PC::ClipDataId& clipDataId,
												IPointCloudClip* clip);

	ConstViewPtr	CreateInvalidPointCloudView	();
	ConstViewPtr	CreateEmptyPointCloudView	(const ConstViewPtr& fromView);
	
	// static helper methods
	static PC::ClipDataId	GetClipDataId	(const PointCloudClipData& clipData);

	// private members
	mutable GS::Lock	mCacheLock;	// guards cache operations

	// Cache contains raw pointers instead of Cachable objects or shared pointers.
	GS::HashTable<PC::PointSourceId, PointCloudCachable*>		mCloudCache;
	GS::HashTable<PC::ClipId, PointCloudClipCachable*>			mClipCache;
	GS::HashTable<PC::ClipDataId, PointCloudClipDataCachable*>	mClipDataCache;
};


// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------

}	// namespace PointCloud

#endif // POINTCLOUDMANAGER_HPP