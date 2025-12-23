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
 * @ingroup Polygon
 *
 * @remarks This enum defines various surface types that can be used in Archicad.
 *          Each surface type is associated with specific elements such as beams, columns, slabs, walls, shells, and roofs.
 *          The types are organized hierarchically, with each category having designated first and last values for better management.
 */
typedef enum {
    /** APISurfaceType_NotSpecified */
    APISurfaceType_NotSpecified = 0,

    /** APISurfaceType_BeamFirst */
    APISurfaceType_BeamFirst = 0x1000,

    /** APISurfaceType_BeamRight */
    APISurfaceType_BeamRight = 0x1000,

    /** APISurfaceType_BeamLeft */
    APISurfaceType_BeamLeft,

    /** APISurfaceType_BeamSide */
    APISurfaceType_BeamSide,

    /** APISurfaceType_BeamTop */
    APISurfaceType_BeamTop,

    /** APISurfaceType_BeamBottom */
    APISurfaceType_BeamBottom,

    /** APISurfaceType_BeamCut */
    APISurfaceType_BeamCut,

    /** APISurfaceType_BeamLast */
    APISurfaceType_BeamLast = APISurfaceType_BeamCut,

    /** APISurfaceType_ColumnFirst */
    APISurfaceType_ColumnFisrt = 0x2000,

    /** APISurfaceType_ColumnTop */
    APISurfaceType_ColumnTop = 0x2000,

    /** APISurfaceType_ColumnBottom */
    APISurfaceType_ColumnBottom,

    /** APISurfaceType_ColumnCoreSide */
    APISurfaceType_ColumnCoreSide,

    /** APISurfaceType_ColumnVeneerSide */
    APISurfaceType_ColumnVeneerSide,

    /** APISurfaceType_ColumnCut */
    APISurfaceType_ColumnCut,

    /** APISurfaceType_ColumnLast */
    APISurfaceType_ColumnLast = APISurfaceType_ColumnCut,

    /** APISurfaceType_SlabFirst */
    APISurfaceType_SlabFirst = 0x3000,

    /** APISurfaceType_SlabTop */
    APISurfaceType_SlabTop = 0x3000,

    /** APISurfaceType_SlabBottom */
    APISurfaceType_SlabBottom,

    /** APISurfaceType_SlabSide */
    APISurfaceType_SlabSide,

    /** APISurfaceType_SlabCut */
    APISurfaceType_SlabCut,

    /** APISurfaceType_SlabLast */
    APISurfaceType_SlabLast = APISurfaceType_SlabCut,

    /** APISurfaceType_WallFirst */
    APISurfaceType_WallFirst = 0x4000,

    /** APISurfaceType_WallRefSide */
    APISurfaceType_WallRefSide = 0x4000,

    /** APISurfaceType_WallOppSide */
    APISurfaceType_WallOppSide,

    /** APISurfaceType_WallSide */
    APISurfaceType_WallSide,

    /** APISurfaceType_WallCut */
    APISurfaceType_WallCut,

    /** APISurfaceType_WallLast */
    APISurfaceType_WallLast = APISurfaceType_WallCut,

    /** APISurfaceType_ShellReferenceFirst */
    APISurfaceType_ShellReferenceFirst = 0x5000,

    /** APISurfaceType_ShellReferenceSide */
    APISurfaceType_ShellReferenceSide = 0x5000,

    /** APISurfaceType_ShellOppositeSide */
    APISurfaceType_ShellOppositeSide,

    /** APISurfaceType_ShellRidge */
    APISurfaceType_ShellRidge,

    /** APISurfaceType_ShellValley */
    APISurfaceType_ShellValley,

    /** APISurfaceType_ShellGable */
    APISurfaceType_ShellGable,

    /** APISurfaceType_ShellHip */
    APISurfaceType_ShellHip,

    /** APISurfaceType_ShellEaves */
    APISurfaceType_ShellEaves,

    /** APISurfaceType_ShellPeak */
    APISurfaceType_ShellPeak,

    /** APISurfaceType_ShellSideWall */
    APISurfaceType_ShellSideWall,

    /** APISurfaceType_ShellEndWall */
    APISurfaceType_ShellEndWall,

    /** APISurfaceType_ShellRTDome */
    APISurfaceType_ShellRTDome,

    /** APISurfaceType_ShellRTHollow */
    APISurfaceType_ShellRTHollow,

    /** APISurfaceType_ShellSide */
    APISurfaceType_ShellSide,

    /** APISurfaceType_ShellCut */
    APISurfaceType_ShellCut,

    /** APISurfaceType_ShellInnerReferenceSide */
    APISurfaceType_ShellInnerReferenceSide,

    /** APISurfaceType_ShellInnerOppositeSide */
    APISurfaceType_ShellInnerOppositeSide,

    /** APISurfaceType_ShellLast */
    APISurfaceType_ShellLast = APISurfaceType_ShellInnerOppositeSide,

    /** APISurfaceType_PlaneRoofFirst */
    APISurfaceType_PlaneRoofFirst = 0x6000,

    /** APISurfaceType_PlaneRoofTop */
    APISurfaceType_PlaneRoofTop = 0x6000,

    /** APISurfaceType_PlaneRoofBottom */
    APISurfaceType_PlaneRoofBottom,

    /** APISurfaceType_PlaneRoofRidge */
    APISurfaceType_PlaneRoofRidge,

    /** APISurfaceType_PlaneRoofValley */
    APISurfaceType_PlaneRoofValley,

    /** APISurfaceType_PlaneRoofGable */
    APISurfaceType_PlaneRoofGable,

    /** APISurfaceType_PlaneRoofHip */
    APISurfaceType_PlaneRoofHip,

    /** APISurfaceType_PlaneRoofEaves */
    APISurfaceType_PlaneRoofEaves,

    /** APISurfaceType_PlaneRoofPeak */
    APISurfaceType_PlaneRoofPeak,

    /** APISurfaceType_PlaneRoofSideWall */
    APISurfaceType_PlaneRoofSideWall,

    /** APISurfaceType_PlaneRoofEndWall */
    APISurfaceType_PlaneRoofEndWall,

    /** APISurfaceType_PlaneRoofRTDome */
    APISurfaceType_PlaneRoofRTDome,

    /** APISurfaceType_PlaneRoofRTHollow */
    APISurfaceType_PlaneRoofRTHollow,

    /** APISurfaceType_PlaneRoofSide */
    APISurfaceType_PlaneRoofSide,

    /** APISurfaceType_PlaneRoofCut */
    APISurfaceType_PlaneRoofCut,

    /** APISurfaceType_PlaneRoofLast */
    APISurfaceType_PlaneRoofLast = APISurfaceType_PlaneRoofCut,

    /** APISurfaceType_PolyRoofFirst */
    APISurfaceType_PolyRoofFirst = 0x7000,

    /** APISurfaceType_PolyRoofTop */
    APISurfaceType_PolyRoofTop = 0x7000,

    /** APISurfaceType_PolyRoofBottom */
    APISurfaceType_PolyRoofBottom,

    /** APISurfaceType_PolyRoofRidge */
    APISurfaceType_PolyRoofRidge,

    /** APISurfaceType_PolyRoofValley */
    APISurfaceType_PolyRoofValley,

    /** APISurfaceType_PolyRoofGable */
    APISurfaceType_PolyRoofGable,

    /** APISurfaceType_PolyRoofHip */
    APISurfaceType_PolyRoofHip,

    /** APISurfaceType_PolyRoofEaves */
    APISurfaceType_PolyRoofEaves,

    /** APISurfaceType_PolyRoofPeak */
    APISurfaceType_PolyRoofPeak,

    /** APISurfaceType_PolyRoofSideWall */
    APISurfaceType_PolyRoofSideWall,

    /** APISurfaceType_PolyRoofEndWall */
    APISurfaceType_PolyRoofEndWall,

    /** APISurfaceType_PolyRoofRTDome */
    APISurfaceType_PolyRoofRTDome,

    /** APISurfaceType_PolyRoofRTHollow */
    APISurfaceType_PolyRoofRTHollow,

    /** APISurfaceType_PolyRoofUndefined */
    APISurfaceType_PolyRoofUndefined,

    /** APISurfaceType_PolyRoofInner */
    APISurfaceType_PolyRoofInner,

    /** APISurfaceType_PolyRoofCut */
    APISurfaceType_PolyRoofCut,

    /** APISurfaceType_PolyRoofLast */
    APISurfaceType_PolyRoofLast = APISurfaceType_PolyRoofCut
} API_SurfaceTypeID;


// ---------------------------------------------------------------------------------------------------------------------

#endif	//APIDEFS_SURFACETYPE_H
