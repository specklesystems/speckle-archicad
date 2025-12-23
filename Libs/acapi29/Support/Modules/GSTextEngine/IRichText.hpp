
// *****************************************************************************
//
//                                Interface IRichText
//
// Module:			TextEngine
// Namespace:		TE
// Contact person:	DGY
//
// SG compatible
//
// *****************************************************************************


#if !defined IRICHTEXT_HPP
#define IRICHTEXT_HPP


// --------------------------------- Includes ----------------------------------

#include "UniString.hpp"
#include "IParagraph.hpp"
#include "CH.hpp"
#include "TEBase.hpp"
#include "Array.hpp"

// ============================== Interface IRichText ==============================

namespace TE {

template <class Type, USize BufferCapacity> class AutoBuffPtr {
protected:
	typedef Type ValueType;

private:
	Type		buffer [BufferCapacity];
	const bool	allocMem;
	Type*		buffPtr;

public:
	AutoBuffPtr (void)
	: allocMem (false), buffPtr (nullptr)
	{ }

	explicit AutoBuffPtr (USize realSize)
	: allocMem	(realSize > BufferCapacity)
	, buffPtr	(nullptr)
	{
		if (allocMem)
			buffPtr = new Type [realSize];
		else
			buffPtr = &buffer [0];
	}

	~AutoBuffPtr (void)	{ if (allocMem && buffPtr != nullptr) delete [] buffPtr; }

	operator const	Type* () const	{ return buffPtr; }
	operator		Type* ()		{ return buffPtr; }

	const	Type* Get () const	{ return buffPtr; }
			Type* Get ()		{ return buffPtr; }

	const	Type& operator[] (Int32 idx) const	{ return buffPtr[idx]; }
			Type& operator[] (Int32 idx)		{ return buffPtr[idx]; }

};



class TE_DLL_EXPORT IRichText {
private:
	void			SetAndGetNextParagraph (IParagraph** paragraph, IRun** firstRun, bool initialize = false);

protected:
	virtual void	CreateParagraphs (void);

public:

		// Destructor

	virtual ~IRichText ();

		// Interface

//	Begin interface
	virtual	GS::UniString&	GetContent	(void) = 0;
	virtual	const GS::UniString&	GetContent	(void) const = 0;
	virtual	void			SetContent (const GS::UniString& content) = 0;

	virtual	double			GetRotAngle	(void) const = 0;
	virtual	double			GetWidthFactor	(void) const = 0;
	virtual	double			GetCharSpaceFactor (void) const = 0;
	virtual	double			GetDefaultTab (void) const = 0;

	virtual	Int32			GetNumOfParagraphs	(void) const = 0;
	virtual IParagraph*		GetParagraph (Int32 paragraphIndex) = 0;
	virtual const IParagraph*	GetParagraph (Int32 paragraphIndex) const = 0;
	virtual void			SetNumOfParagraphs (Int32 numOfParagraphs) = 0;
	virtual void			SetParagraph (Int32 paragraphIndex, const IParagraph& paragraph) = 0;
	virtual void			AddParagraph (const IParagraph& paragraph) = 0;
	virtual	GSCharCode		GetGSCharCode (void) const = 0;

	virtual bool			GetLineWidths (Int32 paragraphIndex, GS::Array <double>* lineLengths) = 0;
	virtual bool			GetLineWidths (Int32 paragraphIndex, GS::Array <double>* lineLengths) const = 0;

//	End interface

// Handler functions
	virtual	Int32			GetNumOfLines (void) const;
	virtual bool			ParagraphIndexFromPos (Int32 charPos, Int32* paragraphIndex) const;
	virtual bool			RunIndexFromPos (Int32 charPos, Int32 *paragraphIndex, Int32* runIndex) const;
	virtual	void			SimpleToRich (const GS::UniString& content, const short* lStarts= nullptr, Int32 lineNum = 0);
	virtual	Int32			CopyAsSimple (GS::UniString* content, short* lStarts, EOLType typeOfParSeparator = EOL_CR) const;
};

}	// namespace TE
// ______________________________ Interface IRichText ______________________________

#endif
