// *********************************************************************************************************************
// Description:		Types for KDTree prdeclaration
//
// Module:			Geometry
// Namespace:		Geometry
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (KDTREE_TYPES_HPP)
#define KDTREE_TYPES_HPP

#pragma once

namespace Geometry {

	enum KDTreeNodeBounds {
		KDTreeNodeBoundsDisabled,
		KDTreeNodeBoundsEnabled,
		KDTreeNodeBoundsOrthogonalPair
	};

	enum KDTreeUpdateMode {
		KDTreeNormalUpdate,
		KDTreeLazyUpdate
	};

	enum KDTreeStatistics {
		KDTreeStatisticsDisabled,
		KDTreeStatisticsEnabled
	};

	enum KDTreeElemSetType {
		KDTreeElemSet,
		KDTreeElemMultiset
	};

	template <typename KeyType, typename ElemType, 
		KDTreeNodeBounds	NodeBoundsMode = KDTreeNodeBoundsDisabled,
		KDTreeUpdateMode	UpdateMode =  KDTreeNormalUpdate,
		KDTreeElemSetType	ElemSetType = KDTreeElemSet,
		KDTreeStatistics	StatisticsMode = KDTreeStatisticsDisabled> 
	class KDTree;

}


#endif