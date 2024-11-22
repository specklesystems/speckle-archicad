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

typedef char DrawIndex;

// these are int-s for historical reasons.
// ... Constants for drawing order ...
const int DrwIndexForSelMarks		= 16;		// special DrwIndex for selection marks 
const int DrwIndexForCameras		= 15;		// special DrwIndex for cameras 
const int MaxDrwIndex				= 14;
const int DrwIndexForTexts			= 10;		// for new text/dimension/cutplane 
const int DrwIndexForLines			= 9;		// for new line/arc/spline/hotspot/beam 
const int DrwIndexForObjects		= 8;		// for new object/light 
const int DrwIndexForStruct			= 7;		// for new wall/colu/ceil/roof/mesh 
const int DrwIndexForHatches		= 6;		// for new hatch/room 
const int DrwIndexForPicts			= 5;		// for new pictobj 
const int DrwIndexForPointClouds	= 1;		// for new point clouds
const int MinDrwIndex				= 1;
const int DrwIndexForGhostElems		= 0;		// special DrwIndex for ghost elements 
const int UnusedDrwIndex			= -1;
const int MasterElemDrwIndexOffset	= 17;		// shifts the drwIndices to range: 18...32 or -2..-16.

inline bool IsDrwIndexForGhostElems (int drawIndex) { return drawIndex == DrwIndexForGhostElems; }


enum class DrawIndexOperation {
	BringToFront		= 0,
	BringForward		= 1,
	SendBackward		= 2,
	SendToBack			= 3,
	DefaultOperation	= 4
};


#endif
