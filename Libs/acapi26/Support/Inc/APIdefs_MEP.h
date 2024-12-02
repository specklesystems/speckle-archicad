// *********************************************************************************************************************
// API definitions - MEP enumerations
//
// Module:			API
// Namespace:		-
// Contact person:	PP, LKJ
//
// [SG compatible]
// *********************************************************************************************************************

#if !defined (APIDEFS_MEP_H)
#define	APIDEFS_MEP_H

#if defined (_MSC_VER)
#pragma once
#endif


// --- Compiler settings -----------------------------------------------------------------------------------------------

// --- Type definitions	------------------------------------------------------------------------------------------------ 


namespace Topology
{
	enum ConnectorShape {
		Rectangular			= 1,
		Circular			= 2,
		Oval				= 3,
		UShape	            = 4
	};

	/*	Three connector classes: Pipe, Duct, Electric */
	enum ConnectorClass
	{
		First				= 1,
		DuctClass			= 1,
		PipeClass			= 2,
		CableCarrierClass	= 3,
		Last				= 3	
	};

	///	Three connection styles
	enum ConnectionStyle
	{
		NoConnector 		= 1,
		Flanged				= 2,
		Overlap				= 3
	};

	///	Flow directions
	enum FlowDirection
	{
		FlowNotDefined		= 0,
		FlowIn				= 1,
		FlowOut				= 2
	};

	///	Connection sex
	enum ConnectionSex
	{
		Unisex				= 0,
		Male				= 1,
		Female				= 2
	};
}	// namespace Topology


// ---------------------------------------------------------------------------------------------------------------------

#endif 
