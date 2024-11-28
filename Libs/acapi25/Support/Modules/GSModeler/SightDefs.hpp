// *****************************************************************************
// Namespaces:        Contact person:
//    Modeler         AACS
//
// SG compatible
// *****************************************************************************

#if !defined(SIGHTDEFS_HPP)
#define SIGHTDEFS_HPP

#pragma once


enum SightIndex {
	InvalidSight = -1, 
	OriginalSight,
	ShadowBodySight,
	ShadowPolygonSight
};

enum ProgressType { 
	PERSPCUT = 0, 
	PROJECTION = 1, 
	ONEPLANESHADOWS = 2,

	NumAllProgreesType = 3
};

#endif //SIGHTDEFS_HPP
