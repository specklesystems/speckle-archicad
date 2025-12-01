// *****************************************************************************
//
//                                Interface IParagraph
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined IPARAGRAPH_HPP
#define IPARAGRAPH_HPP


// --------------------------------- Includes ----------------------------------

#include "ITab.hpp"
#include "IRun.hpp"

// ============================== Interface IParagraph ==============================

namespace TE {

const double SingleSpac	= -1.0;		// Constans for new text spacing
const double OneHalfSpac = -1.5;
const double DoubleSpac	 = -2.0;

class TE_DLL_EXPORT IParagraph {
public:
	// Justification (word alignment) styles (TextEdit.h Macintosh)
	enum Justification {JustLeft = 0, JustCenter = 1, JustRight	= -1, JustFull = 20 };

	virtual ~IParagraph (void);

	virtual Int32	GetFirstPos (void) const = 0;
	virtual Int32	GetRange (void) const = 0;

	virtual void	SetFirstPos (Int32 firstPos) = 0;
	virtual void	SetRange (Int32 range) = 0;

	virtual Int32	GetJustification (void) const = 0;
	virtual double	GetFirstIndent (void) const = 0;
	virtual double	GetIndent (void) const = 0;
	virtual double	GetRightIndent (void) const = 0;
	virtual	double	GetLineSpacing	(void) const = 0;

	virtual Int32	GetTabNum (void) const = 0;
	// From left to right, 0 based
	virtual ITab*	GetTab (Int32 tabIndex) = 0;
	virtual const ITab*	GetTab (Int32 tabIndex) const = 0;

	virtual void	SetNumOfLines (Int32 numOfLines) = 0;
	// lineNum: 0 based
	virtual void	SetEolPos (Int32 lineNum, Int32 eolPos) = 0;
	virtual Int32	GetNumOfLines (void) const = 0;
	virtual Int32	GetEolPos (Int32 lineNum) const = 0;

	virtual bool	LineWidthsIsAvailable (void) const = 0;
	virtual double	GetLineWidth (Int32 lineNum) const = 0;

	virtual Int32	GetNumOfRuns (void) const = 0;
	// runNum: 0 based
	virtual IRun*	GetRun (Int32 runIndex) = 0;
	virtual const IRun*	GetRun (Int32 runIndex) const = 0;
	virtual void	SetNumOfRuns (Int32 numOfRuns) = 0;
	// runNum: 0 based
	virtual void	SetRun (Int32 runIndex, const IRun& run) = 0;
	virtual void	AddRun (const IRun& run) = 0;

	virtual bool	IsIntegrate (void) const = 0;

};

}	// namespace TE
// ______________________________ Interface IParagraph ______________________________

#endif
