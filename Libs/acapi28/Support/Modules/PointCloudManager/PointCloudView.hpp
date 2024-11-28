// *********************************************************************************************************************
// Description:		PointCloudView data structure
//					Provides the high level interface of a viewable point cloud towards the Modeler.
//					http://wiki/w/B-298_Displaying_Point_Clouds_on_Floor_Plan/Overall_Model
//					
// Module:			PointCloudManager
// Namespace:		PointCloud
// Contact person:	BoB
//
// SG compatible
// *********************************************************************************************************************

#if !defined (POINTCLOUDVIEW_HPP)
#define POINTCLOUDVIEW_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include "Definitions.hpp"
#include "SharedObject.hpp"
#include "SharedPtr.hpp"
#include "Lock.hpp"
#include "ClassInfo.hpp"

// from PointCloudLib
#include "IPointCloudClip.hpp"
#include "PCMatrix.hpp"

// from PointCloudManager
#include "PointCloudManagerDefinitions.hpp"
#include "PointCloudViewFwd.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace PC {
	class	Matrix;
	struct	Box;
}

namespace PointCloudTest {
	class PointCloudManagerTest;
}

namespace PointCloud {
	
// --- Constant definitions	--------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------
// Constant class: a PointCloudView instance is never modified after creation, because
// underlying resources are cached by PointCloudManager. Underlying resources, such as
// PointCloud, PointCloudClipData, PointCloudClip and transformation are managed and
// owned by PointCloudManager.
// ---------------------------------------------------------------------------------------------------------------------

// predeclaration of private component
class PointCloudViewResources;

class POINTCLOUDMANAGER_DLL_EXPORT PointCloudView : public GS::SharedObject
{
	static GS::ClassInfo classInfo;

private:
	PointCloudView (const PointCloudView& src);
	PointCloudView& operator= (const PointCloudView& src);

	virtual ~PointCloudView ();
public:

	// operators
	bool			operator== (const PointCloudView& src) const;
	bool			operator!= (const PointCloudView& src) const;

	// methods
	bool						IsValid										() const;
	bool						IsEmpty										() const;
	bool						IsFull										() const;
	bool						IsLoaded									() const;
	USize						GetNumberOfUnclippedPoints					() const;
	const PC::Matrix&			GetDataToViewLocalCoordSysTransformation	() const;
	const PC::PointSourceId&	GetPointSourceId							() const	{ return mPointSourceId; }
	const PC::Box				GetBoundingBox								(const PC::Matrix& outerTran = PC::Matrix::UnitMatrix ()) const;

	IPointCloudClip*			GetClip										() const;

private:
	// only for PointCloudManager
	friend class PointCloudManager;
	
	PointCloudView (const PC::PointSourceId& pointSourceId,
					const PC::ContentId& contentId,
					const PC::ClipDataId& clipDataId,
					const PC::Box& boundingBox,
					const PC::Matrix& transformation,
					const PointCloudViewResources& resources);

	// for PointCloudManager and tests
	friend class PointCloudTest::PointCloudManagerTest;
	const PC::ClipDataId&		GetClipDataId		() const	{ return mClipDataId;		}
	const PC::ContentId&		GetContentId		() const	{ return mContentId;		}
	const PointCloudClipData	GetClipData			() const;

	// private methods
	void LoadCloud () const;
	void Unload () const;
	
	// private members
	mutable GS::Lock			mLoadLock;			// guards LoadCloud
	mutable PC::ContentId		mContentId;			// A default-constructed value means that the point cloud is not loaded already.
													// An @mContentId may be present if the point cloud is not loaded also,
													// because Write writes it out and Read reads it back to check validity.
	mutable PC::Box				mBoundingBox;		// A default-constructed value indicates that the point cloud is loaded
													// but the bounding box is not calculated from the Clip yet.
													// Unloaded point clouds MUST have a bounding box from external source.

	PC::PointSourceId			mPointSourceId;
	PC::ClipDataId				mClipDataId;
	PC::Matrix					mTransformation;

	PointCloudViewResources*	mResources;
};

// --- Variable declarations -------------------------------------------------------------------------------------------

// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace PointCloud

#endif // POINTCLOUDVIEW_HPP