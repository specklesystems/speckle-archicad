// *********************************************************************************************************************
// API definitions - SurfaceType enumeration
//
// Module:			API
// Namespace:		-
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_SURFACETYPE_H)
#define	APIDEFS_SURFACETYPE_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------ 

/**
 * @brief Possible types of a surface.
 * @enum API_SurfaceTypeID
 * @ingroup Polygon
 */
typedef enum {
	APISurfaceType_NotSpecified					= 0,

	APISurfaceType_BeamFirst					= 0x1000,
	APISurfaceType_BeamRight					= 0x1000,
	APISurfaceType_BeamLeft,
	APISurfaceType_BeamSide,
	APISurfaceType_BeamTop,
	APISurfaceType_BeamBottom,
	APISurfaceType_BeamCut,
	APISurfaceType_BeamLast						= APISurfaceType_BeamCut,

	APISurfaceType_ColumnFisrt					= 0x2000,
	APISurfaceType_ColumnTop					= 0x2000,
	APISurfaceType_ColumnBottom,
	APISurfaceType_ColumnCoreSide,
	APISurfaceType_ColumnVeneerSide,
	APISurfaceType_ColumnCut,
	APISurfaceType_ColumnLast					= APISurfaceType_ColumnCut,

	APISurfaceType_SlabFirst					= 0x3000,
	APISurfaceType_SlabTop						= 0x3000,
	APISurfaceType_SlabBottom,
	APISurfaceType_SlabSide,
	APISurfaceType_SlabCut,
	APISurfaceType_SlabLast						= APISurfaceType_SlabCut,

	APISurfaceType_WallFirst					= 0x4000,
	APISurfaceType_WallRefSide					= 0x4000,
	APISurfaceType_WallOppSide,
	APISurfaceType_WallSide,
	APISurfaceType_WallCut,
	APISurfaceType_WallLast						= APISurfaceType_WallCut,

	APISurfaceType_ShellReferenceFirst			= 0x5000,
	APISurfaceType_ShellReferenceSide			= 0x5000,
	APISurfaceType_ShellOppositeSide,
	APISurfaceType_ShellRidge,
	APISurfaceType_ShellValley,
	APISurfaceType_ShellGable,
	APISurfaceType_ShellHip,
	APISurfaceType_ShellEaves,
	APISurfaceType_ShellPeak,
	APISurfaceType_ShellSideWall,
	APISurfaceType_ShellEndWall,
	APISurfaceType_ShellRTDome,
	APISurfaceType_ShellRTHollow,
	APISurfaceType_ShellSide,
	APISurfaceType_ShellCut,
	APISurfaceType_ShellInnerReferenceSide,
	APISurfaceType_ShellInnerOppositeSide,
	APISurfaceType_ShellLast					= APISurfaceType_ShellInnerOppositeSide,

	APISurfaceType_PlaneRoofFirst				= 0x6000,
	APISurfaceType_PlaneRoofTop					= 0x6000,
	APISurfaceType_PlaneRoofBottom,
	APISurfaceType_PlaneRoofRidge,
	APISurfaceType_PlaneRoofValley,
	APISurfaceType_PlaneRoofGable,
	APISurfaceType_PlaneRoofHip,
	APISurfaceType_PlaneRoofEaves,
	APISurfaceType_PlaneRoofPeak,
	APISurfaceType_PlaneRoofSideWall,
	APISurfaceType_PlaneRoofEndWall,
	APISurfaceType_PlaneRoofRTDome,
	APISurfaceType_PlaneRoofRTHollow,
	APISurfaceType_PlaneRoofSide,
	APISurfaceType_PlaneRoofCut,
	APISurfaceType_PlaneRoofLast				= APISurfaceType_PlaneRoofCut,

	APISurfaceType_PolyRoofFirst				= 0x7000,
	APISurfaceType_PolyRoofTop					= 0x7000,
	APISurfaceType_PolyRoofBottom,
	APISurfaceType_PolyRoofRidge,
	APISurfaceType_PolyRoofValley,
	APISurfaceType_PolyRoofGable,
	APISurfaceType_PolyRoofHip,
	APISurfaceType_PolyRoofEaves,
	APISurfaceType_PolyRoofPeak,
	APISurfaceType_PolyRoofSideWall,
	APISurfaceType_PolyRoofEndWall,
	APISurfaceType_PolyRoofRTDome,
	APISurfaceType_PolyRoofRTHollow,
	APISurfaceType_PolyRoofUndefined,
	APISurfaceType_PolyRoofInner,
	APISurfaceType_PolyRoofCut,
	APISurfaceType_PolyRoofLast					= APISurfaceType_PolyRoofCut
} API_SurfaceTypeID;


// ---------------------------------------------------------------------------------------------------------------------

#endif	//APIDEFS_SURFACETYPE_H
