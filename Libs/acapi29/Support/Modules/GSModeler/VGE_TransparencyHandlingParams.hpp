/****************************************************************************/
/*																			*/
/*							Internal Engine TransparencyHandlingParams		*/
/*																			*/
/****************************************************************************/

#ifndef _INTERNALENGINE_TransparencyHandlingParams_H_
#define _INTERNALENGINE_TransparencyHandlingParams_H_

#pragma once

namespace VectorGraphicEngine {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct	TransparencyHandlingParams {
		enum	TransparencyHandlingOption {
			CutWithTransparents,			// cut always, no transparency
			DontCutWithSemiTransparents,	// cut with transparency < K
			DontCutWithFullTransparents,	// cut with transparency < 100
			NotUsed
		};


		TransparencyHandlingParams (TransparencyHandlingOption o) : opts (o) {}

		bool	operator== (const TransparencyHandlingParams& rOp) const								{ return opts == NotUsed || rOp.opts == NotUsed || opts == rOp.opts; }
		bool	operator== (const TransparencyHandlingParams::TransparencyHandlingOption& rOp) const	{ return opts == NotUsed || rOp == NotUsed || opts == rOp; }
		bool	IsUsed () const																			{ return opts != NotUsed; }
	private: 
		TransparencyHandlingOption	opts;
	};

} //VectorGraphicEngine


#endif //_INTERNALENGINE_TransparencyHandlingParams_H_
