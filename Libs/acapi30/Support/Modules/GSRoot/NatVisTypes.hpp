// *********************************************************************************************************************
// Description:		By deriving from GS::NatVis::NatVisTypes, you get member typedefs, which can be used to visualize
//					template parameters, which are in anonymous namespace. The template parameter 'UniqueClass' is used
//					to make the class unique, to ensure that Empty Base Optimization can be applied.
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// *********************************************************************************************************************


#ifndef NATVISTYPES_HPP
#define NATVISTYPES_HPP

#pragma once


namespace GS {
namespace NatVis {


// === class NatVisTypes ===============================================================================================

template <class UniqueClass,
		  class P1  = void, class P2  = void, class P3  = void, class P4  = void, class P5  = void,
		  class P6  = void, class P7  = void, class P8  = void, class P9  = void, class P10 = void,
		  class P11 = void, class P12 = void, class P13 = void, class P14 = void, class P15 = void,
		  class P16 = void, class P17 = void, class P18 = void, class P19 = void, class P20 = void>
class NatVisTypes {
protected:
	using NatVisType1  = P1;
	using NatVisType2  = P2;
	using NatVisType3  = P3;
	using NatVisType4  = P4;
	using NatVisType5  = P5;
	using NatVisType6  = P6;
	using NatVisType7  = P7;
	using NatVisType8  = P8;
	using NatVisType9  = P9;
	using NatVisType10 = P10;
	using NatVisType11 = P11;
	using NatVisType12 = P12;
	using NatVisType13 = P13;
	using NatVisType14 = P14;
	using NatVisType15 = P15;
	using NatVisType16 = P16;
	using NatVisType17 = P17;
	using NatVisType18 = P18;
	using NatVisType19 = P19;
	using NatVisType20 = P20;
};


}	// namespace NatVis
}	// namespace GS


#endif
