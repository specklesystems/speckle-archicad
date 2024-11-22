#ifndef HOTSPOTTYPES_H
#define HOTSPOTTYPES_H

enum HSFlag_t {
	NotGiven_e = 0,
	LineBaseP_e,
	LineMovingP_e,
	LineRefP_e,
	AngleBaseP_e,
	LineOrAngle_e = AngleBaseP_e,  // must be the first angle type
	AngleMovingP_e,
	AngleCenterP_e,
	AngleRefP_e
};

const Int32 HSFlagMask		= 0x007F; // 7 bits enough to cover HSFlag_t (use it whenever a long type flag is converted to HSFlag_t)

// The following status bits can be combined into the flag parameter of the HOTSPOT GDL command
const Int32 HSHideHotspot	= 0x0080;
const Int32 HSEditableFix	= 0x0100;
const Int32 HSReverse2DAngle	= 0x0200;
const Int32 HSUseParAsPaperSize	= 0x0400;

const Int32 HSStatusMask		= 0x0380;		// hotspot attribute without HSUseParAsPaperSize

enum LineKind_t {
	onAxis_1D_e = 0,
	onAxis_2D_e,
	onAxis_3D_e,
	parallel_2D_e,
	parallel_3D_e,
	arcLeg_e,
	arc_e,
	drag_e
};

#endif
