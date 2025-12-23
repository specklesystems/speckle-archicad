/****************************************************************************/
/*																			*/
/*							Internal Engine Defines, enums...				*/
/*																			*/
/****************************************************************************/

#ifndef _INTERNALENGINE_DEFINES_H_
#define _INTERNALENGINE_DEFINES_H_

#pragma once

namespace VectorGraphicEngine {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum SortPolygonsMode {
		ForVisualization,
		ForSweep	
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum ProgressStatusType
	{
		ProgressFullValid, ProgressInvalid, InProgress
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum UpdateSwitch
	{
		FullRebuild,
		UpdateOnly,
		NoUpdateNeccessary
	};


} //end namespace InternalEngine

#endif

