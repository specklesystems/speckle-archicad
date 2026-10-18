// *********************************************************************************************************************
// Typedef for DrawIndex, and global values
//
// Module:			VBUtils
// Namespace:		
// Contact person:	TaB
//
// [SG compatible]
// *********************************************************************************************************************

#ifndef DRAWINDEX_HPP
#define DRAWINDEX_HPP

#include "Definitions.hpp"

using DrawIndex = Int8;

// these are int-s for historical reasons.
// ... Constants for drawing order ...
constexpr int DrwIndexForSelMarks		= 16;		// special DrwIndex for selection marks 
constexpr int DrwIndexForCameras		= 15;		// special DrwIndex for cameras 
constexpr int MaxDrwIndex				= 14;
constexpr int DrwIndexForTexts			= 10;		// for new text/dimension/cutplane 
constexpr int DrwIndexForLines			= 9;		// for new line/arc/spline/hotspot/beam 
constexpr int DrwIndexForObjects		= 8;		// for new object/light 
constexpr int DrwIndexForStruct			= 7;		// for new wall/colu/ceil/roof/mesh 
constexpr int DrwIndexForHatches		= 6;		// for new hatch/room 
constexpr int DrwIndexForPicts			= 5;		// for new pictobj 
constexpr int DrwIndexForPointClouds	= 1;		// for new point clouds
constexpr int MinDrwIndex				= 1;
constexpr int DrwIndexForGhostElems		= 0;		// special DrwIndex for ghost elements 
constexpr int UnusedDrwIndex			= -1;
constexpr int MasterElemDrwIndexOffset	= 17;		// shifts the drwIndices to range: 18...32 or -2..-16.

constexpr bool IsDrwIndexForGhostElems (int drawIndex) { return drawIndex == DrwIndexForGhostElems; }


enum class DrawIndexOperation {
	BringToFront		= 0,
	BringForward		= 1,
	SendBackward		= 2,
	SendToBack			= 3,
	DefaultOperation	= 4
};


#endif
